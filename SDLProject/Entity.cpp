#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

Entity::Entity()
{
    m_position     = glm::vec3(0.0f);
    m_velocity     = glm::vec3(0.0f);
    m_acceleration = glm::vec3(0.0f);
    m_movement = glm::vec3(0.0f);
    m_speed = 0;
    
    m_model_matrix = glm::mat4(1.0f);
    
    m_base_speed = m_speed;
    m_base_damage = m_damage;
    m_attacking = false;
    m_attack_time = 0.0f;
    m_speed_boosted = false;
    m_damage_boosted = false;
    m_speed_boost_timer = 0.0f;
    m_damage_boost_timer = 0.0f;
}

Entity::~Entity()
{
    delete [] m_animation_up;
    delete [] m_animation_down;
    delete [] m_animation_left;
    delete [] m_animation_right;
    delete [] m_walking;
    
}

void Entity::lose_life() {
    num_lives--;
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram *program, GLuint texture_id, int index)
{
    // Step 1: Calculate the UV location of the indexed frame
    float u_coord = (float) (index % m_animation_cols) / (float) m_animation_cols;
    float v_coord = (float) (index / m_animation_cols) / (float) m_animation_rows;
    
    // Step 2: Calculate its UV size
    float width = 1.0f / (float) m_animation_cols;
    float height = 1.0f / (float) m_animation_rows;
    
    // Step 3: Just as we have done before, match the texture coordinates to the vertices
    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };
    
    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };
    
    // Step 4: And render
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());
    
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_position_attribute());
}

void Entity::activate_ai(Entity* player)
{
    switch (m_ai_type) {
        case WALKER:
            ai_walker();
            break;
        case GUARD:
            ai_guard(player);
            break;
        case FLYER:
            ai_flyer(player);
            break;
        case BOSS:
            ai_boss(player);
            break;
        case LURKER:
            ai_lurker(player);
            break;
        case VERTICAL_FLYER:
            ai_vertical_flyer(player);
        default:
            break;
    }
}

void Entity::ai_walker()
{
    m_movement = glm::vec3(0.0f);
}

void Entity::ai_lurker(Entity* player)
{
    float dist = glm::distance(m_position, player->get_position());
    switch(m_ai_state)
    {
        case STATIONARY:
        {
            m_movement = glm::vec3(0.0f, 0.0f, 0.0f);
            if (dist < 2.0f)
            {
                flag = true;
            }
            if(flag && dist > 3.0f)
            {
                flag = false;
                m_ai_state = WALKING;
            }
            break;
        }
        case WALKING:
        {
            glm::vec3 to_player = player->get_position() - m_position;
            if (glm::length(to_player) > 0.0f)
            {
                m_movement = glm::normalize(to_player);
            }
            break;
        }
        default:
            break;
    }
}

void Entity::ai_guard(Entity* player)
{
    switch (m_ai_state)
    {
        case IDLE:
            if (player && glm::distance(m_position, player->get_position()) < 2.5f)
            {
                m_ai_state = WALKING;
            }
            m_movement = glm::vec3(0.0f);
            break;
        case WALKING:
            if (player)
            {
                if (m_position.x > player->get_position().x)
                {
                    m_movement.x = -1.0f;
                }
                else {
                    m_movement.x = 1.0f;
                }
                if (m_position.y > player->get_position().y)
                {
                    m_movement.y = -1.0f;
                }
                else {
                    m_movement.y = 1.0f;
                }
            }
            else
            {
                if (m_movement.x > 0)
                {
                    m_facing = RIGHT;
                }
                else if (m_movement.x < 0)
                {
                    m_facing = LEFT;
                }
                if (m_movement.y > 0)
                {
                    m_facing = UP;
                }
                else if (m_movement.y < 0)
                {
                    m_facing = DOWN;
                }
                m_animation_indices = m_walking[m_facing];
            }
            break;
        case ATTACKING:
            m_movement = glm::vec3(0.0f);
            break;
        default:
            break;
    }
}

void Entity::ai_flyer(Entity* player)
{
    switch (m_ai_state)
    {
        case WALKING:
            if (m_position.x >= 16.0f)
            {
                m_flyer_direc = -1.0f;
            }
            else if (m_position.x <= 5.0f)
            {
                m_flyer_direc = 1.0f;
            }
            m_movement.x = m_flyer_direc;
            m_movement.y = 0.0f;
        case ATTACKING:
            if (player)
            {
                glm::vec3 to_player = player->get_position() - m_position;
                float distance = glm::length(to_player);
                if (distance <= 3.0f)
                {
                    glm::vec3 direction = glm::normalize(to_player);
                    m_movement.x = direction.x;
                    m_movement.y = direction.y;
                }
                else
                {
                    m_ai_state = WALKING;
                }
            }
        default:
            break;
    }
}
void Entity::ai_vertical_flyer(Entity* player)
{
    switch (m_ai_state)
    {
        case WALKING:
            if (m_position.y <= -18.0f)
            {
                m_flyer_direc = 1.0f;
            }
            else if (m_position.y >= -13.0f)
            {
                m_flyer_direc = -1.0f;
            }
            m_movement.y = m_flyer_direc;
            m_movement.x = 0.0f;
        case ATTACKING:
            if (player)
            {
                glm::vec3 to_player = player->get_position() - m_position;
                float distance = glm::length(to_player);
                if (distance <= 3.0f)
                {
                    glm::vec3 direction = glm::normalize(to_player);
                    m_movement.x = direction.x;
                    m_movement.y = direction.y;
                }
                else
                {
                    m_ai_state = WALKING;
                }
            }
        default:
            break;
    }
}

void Entity::ai_boss(Entity* player)
{
    if (player)
    {
        glm::vec3 to_player = player->get_position() - m_position;
        float distance = glm::length(to_player);

        if (distance <= 5.0f)
        {
            glm::vec3 direction = glm::normalize(to_player);
            m_movement.x = direction.x;
            m_movement.y = direction.y;
            if (direction.x  > 0)
            {
                m_facing = RIGHT;
            }
            else
            {
                m_facing = LEFT;
            }
        }
        else
        {
            m_movement.x = 0.0f;
            m_movement.y = 0.0f;
        }
    }
}

void Entity::update(float delta_time, Entity* player, Entity* objects, int object_count, Map* map)
{
    if (m_entity_type == PLAYER && m_invuln_timer > 0.0f)
    {
        m_invuln_timer = std::max(0.0f, m_invuln_timer - delta_time);
    }
    
    if (m_is_hit)
    {
        m_hit_animation_time += delta_time;
        float frame_duration = 0.3f/(float)m_hit_animation_frames;
        if (m_hit_animation_time >= frame_duration)
        {
            m_hit_animation_time = 0.0f;
            m_animation_index++;
            if (m_animation_index >= m_hit_animation_frames)
            {
                m_is_hit= false;
                m_animation_index = 0;
            }
        }
    }
    if (m_entity_type == ENEMY && m_ai_type == BOSS && m_is_attacking)
    {
        m_attack_animation_time += delta_time;
        float frame_duration = 0.3f /(float)m_attack_animation_frames;
        if (m_attack_animation_time >= frame_duration)
        {
            m_attack_animation_time = 0.0f;
            m_animation_index++;
            if (m_animation_index >= m_attack_animation_frames)
            {
                m_animation_index = 0;
                m_is_attacking = false;
                m_ai_state = WALKING;
            }
        }
        return;
    }
    if (!m_is_active) return;

    if (glm::length(m_movement)!= 0)
    {
        m_animation_time += delta_time;
        float frames_per_second = (float)1.0f/SECONDS_PER_FRAME;
        if (m_animation_time >= frames_per_second)
        {
            m_animation_time = 0.0f;
            m_animation_index++;
            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }
    }

    if (m_entity_type == ENEMY)
    {
        activate_ai(player);
//        if (glm::length(m_movement) > 0.0f) {
//                if (fabs(m_movement.x) > fabs(m_movement.y))
//                {
//                    if (m_movement.x > 0.0)
//                    {
//                        m_facing = UP;
//                    }
//                    else
//                    {
//                        m_facing = DOWN;
//                    }
//                }
//                else
//                {
//                    if (m_movement.y > 0.0)
//                    {
//                        m_facing = UP;
//                    }
//                    else{
//                        m_facing = DOWN;
//                    }
//                    //m_facing = (m_movement.y > 0.0f ? UP : DOWN);
//                }
//                m_animation_indices = m_walking[m_facing];
//            }
    }
    
    // Our character moves from left to right, so they need an initial velocity
    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed;
    // Now we add the rest of the gravity physics
    m_velocity += m_acceleration * delta_time;

    m_position.y += m_velocity.y * delta_time;
    check_collision_y(objects, object_count);
    check_collision_y(map);

    m_position.x += m_velocity.x * delta_time;
    check_collision_x(objects, object_count);
    check_collision_x(map);

    // Jump
    if (m_is_jumping)
    {
        // STEP 1: Immediately return the flag to its original false state
        m_is_jumping = false;
        
        // STEP 2: The player now acquires an upward velocity
        m_velocity.y += m_jumping_power;
    }

    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
}

void const Entity::check_collision_y(Entity* collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity *collidable_entity = &collidable_entities[i];
        if (!collidable_entity->m_is_active) continue;
        
        if (check_collision(collidable_entity))
        {
            float y_distance = fabs(m_position.y - collidable_entity->m_position.y);
            float y_overlap = fabs(y_distance - (m_height / 2.0f) - (collidable_entity->m_height / 2.0f));
            if (m_position.y > 0)
            {
                m_position.y   -= y_overlap;
                m_velocity.y    = 0;
                m_collided_top  = true;
            }
            else if (m_velocity.y < 0)
            {
                m_position.y      += y_overlap;
                m_velocity.y       = 0;
                m_collided_bottom  = true;
            }
            if (collidable_entity->m_entity_type == PLAYER && m_entity_type == ENEMY)
            {
                Entity* player_entity = collidable_entity;
                
                if (player_entity->m_invuln_timer <= 0.0f)
                {
                    player_entity->m_health -= m_damage;
                    player_entity->m_invuln_timer = 1.0f;
                    if (player_entity->m_health <= 0)
                    {
                        player_entity->m_health = 0;
                    }
                }
                if (m_ai_type == BOSS)
                {
                    m_ai_state= ATTACKING;
                    m_is_attacking = true;
                    m_attack_animation_time = 0.0f;
                    m_animation_index = 0;
                }
            }
            if (m_entity_type == PLAYER && collidable_entity->m_entity_type == ENEMY && m_velocity.y < 0)
            {
                collidable_entity->deactivate();
            }
            if (m_entity_type == PLAYER && collidable_entity->m_entity_type == ITEM)
            {
                collidable_entity->deactivate();
            }
        }
    }
}

void const Entity::check_collision_x(Entity* collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity *collidable_entity = &collidable_entities[i];
        if (!collidable_entity->m_is_active) continue;
        
        if (check_collision(collidable_entity))
        {
            float x_distance = fabs(m_position.x - collidable_entity->m_position.x);
            float x_overlap = fabs(x_distance - (m_width / 2.0f) - (collidable_entity->m_width / 2.0f));
            if (m_velocity.x > 0)
            {
                m_position.x    -= x_overlap;
                m_velocity.x     = 0;
                m_collided_right = true;
            }
            else if (m_velocity.x < 0)
            {
                m_position.x   += x_overlap;
                m_velocity.x    = 0;
                m_collided_left = true;
            }
            if (collidable_entity->m_entity_type == PLAYER && m_entity_type == ENEMY)
            {
                Entity* player_entity = collidable_entity;
                if (player_entity->m_invuln_timer <= 0.0f)
                {
                    player_entity->m_health -= m_damage;
                    player_entity->m_invuln_timer = 1.0f;
                    if (player_entity->m_health <= 0)
                    {
                        player_entity->m_health = 0;
                    }
                }
                if (m_ai_type == BOSS)
                {
                    m_ai_state= ATTACKING;
                    m_is_attacking = true;
                    m_attack_animation_time = 0.0f;
                    m_animation_index = 0;
                }
            }
            if (m_entity_type == PLAYER && collidable_entity->m_entity_type == ITEM)
            {
                collidable_entity->deactivate();
            }
        }
    }
}

// Probes for tiles
void const Entity::check_collision_y(Map* map) {
    glm::vec3 top = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_left = glm::vec3(m_position.x - (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_right = glm::vec3(m_position.x + (m_width / 2), m_position.y + (m_height / 2), m_position.z);

    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_left  = glm::vec3(m_position.x - (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_right = glm::vec3(m_position.x + (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    
    float penetration_x = 0.0f;
    float penetration_y = 0.0f;
    
    if (map->is_solid(top, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
}

void const Entity::check_collision_x(Map* map)
{
    // Probes for tiles
    glm::vec3 left  = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);
    
    float penetration_x = 0.0f;
    float penetration_y = 0.0f;

    if (map->is_solid(left, &penetration_x, &penetration_y) && m_velocity.x < 0)
    {
        m_position.x += penetration_x;
        m_velocity.x = 0;
        m_collided_left = true;
    }
    if (map->is_solid(right, &penetration_x, &penetration_y) && m_velocity.x > 0)
    {
        m_position.x -= penetration_x;
        m_velocity.x = 0;
        m_collided_right = true;
    }
}

void Entity::render(ShaderProgram* program)
{
    if (!m_is_active)
    {
        return;
    }
    if (m_animation_cols <= 0)
    {
        m_animation_cols = 1;
    }
    if (m_animation_rows <= 0)
    {
        m_animation_rows = 1;
    }
    m_model_matrix = glm::translate(glm::mat4(1.0f), m_position);
    program->set_model_matrix(m_model_matrix);
    
    if (m_entity_type == ENEMY && m_ai_type == BOSS)
    {
        m_model_matrix = glm::scale(m_model_matrix, glm::vec3(get_width(), get_height(), 1.0f));
    }
    program->set_model_matrix(m_model_matrix);

    if (m_entity_type == PLAYER)
    {
        int idleIndex = 0;

        if (m_facing == LEFT)
        {
            idleIndex = 2;
        }
        else if (m_facing == RIGHT)
        {
            idleIndex = 3;
        }
        else if (m_facing == UP)
        {
            idleIndex = 1;
        }
        else{
            idleIndex = 0;
        }
        if (glm::length(m_movement) == 0)
        {
            draw_sprite_from_texture_atlas(program, m_idle_texture_id, idleIndex);
        }
        else
        {
            draw_sprite_from_texture_atlas(program, m_run_texture_id, m_animation_indices[m_animation_index]);
        }
    }
    else if (m_entity_type == ENEMY && m_ai_type == BOSS && m_is_hit)
    {

        int prev_cols = m_animation_cols;
        int prev_rows = m_animation_rows;
        m_animation_cols = m_hit_animation_cols;
        m_animation_rows = m_hit_animation_rows;
        draw_sprite_from_texture_atlas(program, boss_hit_texture_id, m_hit_animation_indices[m_animation_index]);
        m_animation_cols = prev_cols;
        m_animation_rows = prev_rows;
        return;
    }
    else if (m_entity_type == ENEMY && m_ai_type == BOSS && m_is_attacking &&m_has_attack_sprites)
    {
        int prev_cols = m_animation_cols, prev_rows = m_animation_rows;
        m_animation_cols = m_attack_animation_cols;
        m_animation_rows = m_attack_animation_rows;

        if (m_facing == LEFT)
        {
            draw_sprite_from_texture_atlas(program,boss_attack_left_texture_id,m_attack_left_indices[m_animation_index]);
        }
        else {
            draw_sprite_from_texture_atlas(program,boss_attack_right_texture_id, m_attack_right_indices[m_animation_index]);
        }
        m_animation_cols = prev_cols;
        m_animation_rows = prev_rows;
        return;
    }
    
    else if (m_entity_type == ENEMY) {
        
        if (m_animation_indices != NULL)
        {
            draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
        }
        else
        {
            float vertices[]   = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
            float tex_coords[] = {  0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };

            glBindTexture(GL_TEXTURE_2D, m_texture_id);
            
            glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
            glEnableVertexAttribArray(program->get_position_attribute());
            glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
            glEnableVertexAttribArray(program->get_tex_coordinate_attribute());
            
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glDisableVertexAttribArray(program->get_position_attribute());
            glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
        }
    }
    else if (m_entity_type == ITEM)
    {
        float vertices[]   = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
        float tex_coords[] = {  0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };
        
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        
        glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->get_position_attribute());
        glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
        glEnableVertexAttribArray(program->get_tex_coordinate_attribute());
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDisableVertexAttribArray(program->get_position_attribute());
        glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
    }
}

bool const Entity::check_collision(Entity* other) const
{
    // If we are checking with collisions with ourselves, this should be false
    if (other == this) return false;
    
    // If either entity is inactive, there shouldn't be any collision
    if (!m_is_active || !other->m_is_active) return false;

    float x_dist = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float y_dist = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);

    return (x_dist < 0.0f && y_dist < 0.0f);
}
