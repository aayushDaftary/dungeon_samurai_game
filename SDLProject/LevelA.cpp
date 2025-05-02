#include "LevelA.h"
#include "Utility.h"
#include "Effects.h"
#define LEVEL_WIDTH 34
#define LEVEL_HEIGHT 10
//#define ENEMY_COUNT 3
#define ITEM_COUNT 1

//Effects *g_effects = nullptr;

unsigned int LEVELA_DATA[] =
{
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 1, 1, 4, 2, 2, 1, 1, 4, 1, 1, 1, 4, 2, 1, 4, 2, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 1, 1, 1, 1, 1, 4, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 1, 1, 1, 1, 2, 1, 2, 1, 3, 3, 3, 1, 2, 2, 1, 1, 1, 1, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    3, 1, 2, 1, 1, 1, 1, 4, 1, 2, 2, 4, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete[] m_game_state.items;
    delete m_game_state.player;
    delete m_game_state.map;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.heal_sfx);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelA::initialise(int lives)
{
    this->lives = lives;
    m_game_state.next_scene_id = -1;
    //m_game_state.player->magma_exposure = 0.0f;
    
    //GLuint grass_tex = Utility::load_texture("TX Tileset Grass.png");
    GLuint grass_tex = Utility::load_texture("basictiles.png");
    //GLuint wall_tex = Utility::load_texture("TX Tileset Wall.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA,grass_tex, 1.0f,8,15);

    m_game_state.player = new Entity();
    m_game_state.player->set_entity_type(PLAYER);
    m_game_state.player->on_magma = false;
    
    m_game_state.player->set_position(glm::vec3(1.5f, -1.0f, 0.0f));
    m_game_state.player->set_movement(glm::vec3(0.0f));
    m_game_state.player->m_speed = 2.5f;
    m_game_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    
    m_game_state.player->m_animation_cols = 4;
    m_game_state.player->m_animation_rows = 7;
    m_game_state.player->m_animation_frames = 5;
    m_game_state.player->m_walking[Entity::DOWN] = new int[5]{  4,  8, 12, 16, 20 };
    m_game_state.player->m_walking[Entity::UP] = new int[5]{  5,  9, 13, 17, 21 };
    m_game_state.player->m_walking[Entity::LEFT] = new int[5]{  6, 10, 14, 18, 22 };
    m_game_state.player->m_walking[Entity::RIGHT] = new int[5]{  7, 11, 15, 19, 23 };

    m_game_state.player->m_animation_indices = m_game_state.player->m_walking[Entity::DOWN];
    m_game_state.player->m_animation_index = 0;
    m_game_state.player->m_animation_time = 0.0f;
    m_game_state.player->m_run_texture_id = Utility::load_texture("redsamurai.png");
    m_game_state.player->m_idle_texture_id = Utility::load_texture("redsamurai.png");

    m_game_state.player->set_height(0.8f);
    m_game_state.player->set_width(0.8f);
    //m_game_state.player->m_jumping_power = 7.0f;

    //player hp and dmg
    m_game_state.player->m_health = 100;
    //sword damge
    m_game_state.player->m_damage = 10;
    m_game_state.player->m_base_speed = m_game_state.player->m_speed;
    m_game_state.player->m_base_damage = m_game_state.player->m_damage;

    //enemies
    GLuint enemy_texture_id = Utility::load_texture("spirit.png");
    //GLuint boss_texture_id = Utility::load_texture("boss.png");
    m_number_of_enemies = ENEMY_COUNT;
    m_game_state.enemies = new Entity[ENEMY_COUNT];
    for (int i = 0; i < m_number_of_enemies; i++)
    {
        Entity& enemy = m_game_state.enemies[i];
        enemy.m_animation_cols = 4;
        enemy.m_animation_rows = 4;
        enemy.m_animation_frames = 4;
        enemy.m_walking[Entity::DOWN] = new int[4]{ 0,  4,  8, 12 };
        enemy.m_walking[Entity::UP] = new int[4]{ 1,  5,  9, 13 };
        enemy.m_walking[Entity::LEFT] = new int[4]{ 2,  6, 10, 14 };
        enemy.m_walking[Entity::RIGHT] = new int[4]{ 3,  7, 11, 15 };
        enemy.m_animation_indices = enemy.m_walking[Entity::DOWN];
        enemy.m_animation_index = 0;
        enemy.m_animation_time = 0.0f;
    }

    m_game_state.enemies[0].set_entity_type(ENEMY);
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    m_game_state.enemies[0].m_texture_id = enemy_texture_id;
    m_game_state.enemies[0].set_position(glm::vec3(5.0f, -7.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[0].m_speed = 1.0f;
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[0].m_health = 20;
    m_game_state.enemies[0].m_damage = 10;

    m_game_state.enemies[1].set_entity_type(ENEMY);
    m_game_state.enemies[1].set_ai_type(GUARD);
    m_game_state.enemies[1].set_ai_state(IDLE);
    m_game_state.enemies[1].m_texture_id = enemy_texture_id;
    m_game_state.enemies[1].set_position(glm::vec3(10.0f, -4.5f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[1].m_speed = 1.5f;
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].m_health = 20;
    m_game_state.enemies[1].m_damage = 10;

    // big boss
    m_game_state.enemies[2].set_entity_type(ENEMY);
    m_game_state.enemies[2].set_ai_type(BOSS);
    m_game_state.enemies[2].set_ai_state(IDLE);
//    m_game_state.enemies[2].m_animation_cols = 4;
//    m_game_state.enemies[2].m_animation_rows = 1;
//    m_game_state.enemies[2].m_animation_frames = 4;
    m_game_state.enemies[2].m_texture_id = enemy_texture_id;
    m_game_state.enemies[2].set_height(3.0f);
    m_game_state.enemies[2].set_width(3.0f);
    m_game_state.enemies[2].set_position(glm::vec3(17.5f, -4.0f, 0.0f));
    m_game_state.enemies[2].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[2].m_speed = 1.2f;
    m_game_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[2].m_health = 50;
    m_game_state.enemies[2].m_damage = 15;

    // Items
    m_number_of_items = ITEM_COUNT;
    m_game_state.items = new Entity[ITEM_COUNT];
    
    GLuint medpack_texture_id = Utility::load_texture("medpack.png");
    m_game_state.items[0].set_entity_type(ITEM);
    m_game_state.items[0].m_texture_id = medpack_texture_id;
    m_game_state.items[0].item_type = Entity::MEDPACK;
    m_game_state.items[0].set_position(glm::vec3(8.0f, -4.0f, 0.0f));
    m_game_state.items[0].set_movement(glm::vec3(0.0f));
    m_game_state.items[0].m_speed = 0.0f;
    m_game_state.items[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.items[0].set_height(1.0f);
    m_game_state.items[0].set_width(1.0f);
    m_game_state.items[0].m_health = 0;
    m_game_state.items[0].m_damage = 0;

    /**
     BGM and SFX
     */

    m_game_state.bgm = nullptr;
    m_game_state.jump_sfx = nullptr;
    m_game_state.heal_sfx = Mix_LoadWAV("heal.wav");
    m_game_state.death_sfx = Mix_LoadWAV("death.wav");
    
    m_game_state.m_sword = new Entity();
    m_game_state.m_sword->set_entity_type(SWORD);
    m_game_state.m_sword->m_texture_id = Utility::load_texture("sword.png");
    m_game_state.m_sword->set_position(glm::vec3(-100.0f,-100.0f,0.0f));
    m_game_state.m_sword->m_sword_timer = 0.0f;
    
    m_game_state.m_sword->m_animation_cols = 1;
    m_game_state.m_sword->m_animation_rows = 1;
    m_game_state.m_sword->m_animation_frames = 1;
    m_game_state.m_sword->m_animation_indices = nullptr;
    
    
}

void LevelA::update(float delta_time)
{
    Entity* player = m_game_state.player;
    Entity* m_sword = m_game_state.m_sword;
    Map* map = m_game_state.map;

    player->update(delta_time, player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, player, player, 1, map);
    }

    for (int j = 0; j < m_number_of_items; j++)
    {
        Entity* item = &m_game_state.items[j];
        if (!item->is_active() || !player->check_collision(item)) continue;

        switch (item->item_type)
        {
            case Entity::MEDPACK:
                Mix_PlayChannel(-1, m_game_state.heal_sfx, 0);
                player->m_health = 100;
                item->deactivate();
                break;
            default:
                break;
        }
    }

    if (player->m_attacking)
    {
        //sword direction
        glm::vec3 offset;
        switch (player->m_facing)
        {
            case Entity::LEFT:
                offset = {-1.0f,0.0f,0.0f};
                break;
            case Entity::RIGHT:
                offset = {1.0f,0.0f,0.0f};
                break;
            case Entity::UP:
                offset = {0.0f,1.0f,0.0f};
                break;
            default:
                offset = {0.0f,-1.0f,0.0f};
                break;
        }
        m_sword->set_position(player->get_position() + offset);

        if (!player->m_hasHitThisSwing)
        {
            for (int i = 0; i < ENEMY_COUNT; i++)
            {
                Entity* enemy = &m_game_state.enemies[i];
                if (enemy->is_active() && m_sword->check_collision(enemy))
                {
                    enemy->m_health -= player->m_damage;
                    player->m_hasHitThisSwing = true;
                    if (enemy->m_health <= 0)
                    {
                        enemy->deactivate();
                    }
                    break;
                }
            }
        }

        m_sword->m_sword_timer += delta_time;
        if (m_sword->m_sword_timer >= Entity::SWING_DURATION)
        {
            player->m_attacking = false;
            m_sword->m_sword_timer = 0.0f;
        }
    }
    
    //getss tileIndex that player is on
    float tx = (player->get_position().x + map->get_tile_size() * 0.5f)/ map->get_tile_size();
    float ty = -(player->get_position().y - map->get_tile_size() * 0.5f)/ map->get_tile_size();
    int tile_x = (int)floor(tx);
    int tile_y = (int)floor(ty);

    unsigned int tile = 0;
    if (tile_x >= 0 && tile_x < LEVEL_WIDTH &&tile_y >= 0 && tile_y < LEVEL_HEIGHT)
    {
        tile = m_game_state.map->get_level_data()[tile_y * LEVEL_WIDTH + tile_x];
    }
    
    //magma effect
    bool nowOnMagma = (tile == 5);
    if (nowOnMagma && !player->on_magma)
    {
        m_effects->start(LAVA, 1.0f / 3.0f);
    }
    else if (!nowOnMagma && player->on_magma)
    {
        m_effects->start(NONE, 0.0f);
    }
    player->on_magma = nowOnMagma;

    if (nowOnMagma)
    {
        player->magma_timer += delta_time;
        if (player->magma_timer >= 1.0f)
        {
            player->m_health = std::max(0, player->m_health - 10);
            player->magma_timer = 0.0f;
        }
    }
    else
    {
        
        player->magma_timer = 0.0f;
    }

    //death
    if (player->m_health <= 0)
    {
        lives -= 1;
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);
        if (lives > 0)
        {
            player->m_health = 100;
            player->set_position(glm::vec3(1.5f, -1.0f, 0.0f));
        }
        else
        {
            m_game_state.next_scene_id = 1;
        }
    }
    
    bool boss_defeated = !m_game_state.enemies[2].is_active();
    static bool door_spawned = false;
    if (boss_defeated && !door_spawned)
    {
        door_spawned = true;
        m_number_of_items += 1;
        Entity* door = &m_game_state.items[0];
        door->activate();
        door->set_entity_type(ITEM);
        door->item_type = Entity::DOOR;
        door->m_texture_id = Utility::load_texture("door.png");
        door->set_position(glm::vec3(33.0f, -4.0f, 0.0f));
        door->set_movement(glm::vec3(0.0f));
        door->m_speed = 0.0f;
        door->set_height(1.0f);
        door->set_width(1.0f);
    }
    if (m_game_state.items && m_game_state.items[0].is_active() && m_game_state.items[0].item_type == Entity::DOOR)
    {
        Entity* door = &m_game_state.items[0];
        if (player->check_collision(door))
        {
            m_game_state.next_scene_id = 2;
            door_spawned = false;
        }
    }
}

void LevelA::render(ShaderProgram* program)
{
    Entity* player = m_game_state.player;
    Entity* sword = m_game_state.m_sword;
    Map* map = m_game_state.map;

    map->render(program);
    player->render(program);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), player->get_position());

    float baseAngle = 0.0f;
    switch (player->m_facing)
    {
        case Entity::LEFT:
            baseAngle = glm::radians(180.0f);
            break;
        case Entity::RIGHT:
            baseAngle = glm::radians(0.0f);
            break;
        case Entity::UP:
            baseAngle = glm::radians(90.0f);
            break;
        case Entity::DOWN:
            baseAngle = glm::radians(-90.0f);
            break;
    }

    if (sword->m_sword_timer > 0.0f)
    {
        float t= sword->m_sword_timer / Entity::SWING_DURATION;
        float swingA = glm::radians(-90.0f+180.0f*t);
        baseAngle += swingA;
    }

    model = glm::rotate(model, baseAngle, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3(0.8f, 0.0f, 0.0f));
    //fixes direction of sword based on plyer direction
    if(player->m_facing == Entity::LEFT)
    {
        model = glm::scale(model,glm::vec3(0.6f, -0.6f, 1.0f));
    }
    else
    {
        model = glm::scale(model,glm::vec3(0.6f, 0.6f, 1.0f));
    }
    program->set_model_matrix(model);
    sword->draw_sprite_from_texture_atlas(program, sword->m_texture_id, 0);
     
    for (int i = 0; i < m_number_of_enemies; i++)
    {
        m_game_state.enemies[i].render(program);
    }
    for (int i = 0; i < m_number_of_items; i++)
    {
        m_game_state.items[i].render(program);
    }
}
