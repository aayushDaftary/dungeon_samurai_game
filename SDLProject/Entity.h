#pragma once
#include "Map.h"

enum EntityType { PLATFORM, PLAYER, ENEMY, ITEM, SWORD  };
enum AIType     { WALKER, GUARD, FLYER, BOSS, LURKER, VERTICAL_FLYER            };
enum AIState    { WALKING, IDLE, ATTACKING, STATIONARY };

class Entity
{
private:
    bool m_is_active = true;
    EntityType m_entity_type;
    AIType m_ai_type;
    AIState m_ai_state;
    
    int *m_animation_right = NULL; // move to the right
    int *m_animation_left  = NULL; // move to the left
    int *m_animation_up    = NULL; // move upwards
    int *m_animation_down  = NULL; // move downwards
    
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;
    
    float m_width  = 1.0f;
    float m_height = 1.0f;
    float m_flyer_direc = 1.0f;
    
public:
    // Static attributes
    static constexpr float SWING_DURATION = 0.2f;
    static constexpr float LURKER_NEAR_DISTANCE  = 1.0f;
    static constexpr float LURKER_CHASE_DISTANCE = 3.0f;
    
    static const int SECONDS_PER_FRAME = 4;
    static const int MEDPACK = 1, SPEEDBOOST = 2, DAMAGEBOOST = 3, DOOR = 4;
    static const int LEFT  = 2,
                     RIGHT = 3,
                     UP    = 1,
                     DOWN  = 0;
    
    // Existing
    GLuint m_texture_id;
    glm::mat4 m_model_matrix;
    
    GLuint m_run_texture_id;
    GLuint m_idle_texture_id;
    int num_lives = 1;
    bool flag = false;
   
    // Translating
    float m_speed;
    glm::vec3 m_movement;
    
    // Animating
    int **m_walking          = new int*[4] { m_animation_left, m_animation_right, m_animation_up, m_animation_down };
    int *m_animation_indices = NULL;
    int m_animation_frames   = 1;
    int m_animation_index    = 0;
    float m_animation_time   = 0.0f;
    int m_animation_cols     = 0;
    int m_animation_rows     = 0;
    
    // Jumping
    bool m_is_jumping     = false;
    float m_jumping_power = 0.0f;
    
    // Colliding
    bool m_collided_top    = false;
    bool m_collided_bottom = false;
    bool m_collided_left   = false;
    bool m_collided_right  = false;
    
    //player vars
    int m_health = 0;
    int m_damage = 0;
    int item_type = 0;
    bool m_attacking = false;
    float m_attack_time = 0.0f;
    bool  m_hasHitThisSwing = false;
    int m_facing = DOWN;
    bool m_speed_boosted = false;
    bool m_damage_boosted = false;
    float m_speed_boost_timer = 0.0f;
    float m_damage_boost_timer = 0.0f;
    float m_base_speed = 0.0f;
    float m_base_damage = 0.0f;
    float m_invuln_timer = 0.0f;
    float m_sword_timer = 0.0f;
    float magma_timer = 0.0f;
    float magma_exposure = 0.0f;
    bool on_magma = false;
    bool win_flag = false;
    
    //boss getting hit vars
    GLuint boss_hit_texture_id = 0;
    int    m_hit_animation_cols = 0;
    int    m_hit_animation_rows= 0;
    int    m_hit_animation_frames = 0;
    int*   m_hit_animation_indices= nullptr;
    float  m_hit_animation_time = 0.0f;
    bool   m_is_hit = false;
    
    //boss attacking vars
    GLuint boss_attack_left_texture_id  = 0;
    GLuint boss_attack_right_texture_id = 0;
    int    m_attack_animation_cols = 4;
    int    m_attack_animation_rows = 1;
    int    m_attack_animation_frames = 4;
    int*   m_attack_left_indices = nullptr;
    int*   m_attack_right_indices = nullptr;
    float  m_attack_animation_time = 0.0f;
    bool   m_is_attacking = false;
    
    bool m_has_attack_sprites = false;
    
    // Methods
    Entity();
    ~Entity();
    void lose_life();
    void draw_sprite_from_texture_atlas(ShaderProgram *program, GLuint texture_id, int index);
    void update(float delta_time, Entity *player, Entity *objects, int object_count, Map *map);
    void render(ShaderProgram *program);
    void activate_ai(Entity *player);
    void ai_walker();
    void ai_guard(Entity *player);
    void ai_flyer(Entity *player);
    void ai_boss(Entity* player);
    void ai_lurker(Entity* player);
    void ai_vertical_flyer(Entity* player);
    //void ai_stationary();
    void const check_collision_y(Entity *collidable_entities, int collidable_entity_count);
    void const check_collision_x(Entity *collidable_entities, int collidable_entity_count);
    void const check_collision_y(Map *map);
    void const check_collision_x(Map *map);
    
    bool const check_collision(Entity *other) const;
    
    void activate()   { m_is_active = true;  };
    void deactivate() { m_is_active = false; };
    
    bool is_active() const { return m_is_active; }
    EntityType const get_entity_type()    const { return m_entity_type;   };
    AIType     const get_ai_type()        const { return m_ai_type;       };
    AIState    const get_ai_state()       const { return m_ai_state;      };
    glm::vec3  const get_position()       const { return m_position;      };
    glm::vec3  const get_movement()       const { return m_movement;      };
    glm::vec3  const get_velocity()       const { return m_velocity;      };
    glm::vec3  const get_acceleration()   const { return m_acceleration;  };
    float      const get_jumping_power () const { return m_jumping_power; };
    float      const get_speed()          const { return m_speed;         };
    int        const get_width()          const { return m_width;         };
    int        const get_height()         const { return m_height;        };
    
    void const set_entity_type(EntityType new_entity_type)  { m_entity_type   = new_entity_type;      };
    void const set_ai_type(AIType new_ai_type)              { m_ai_type       = new_ai_type;          };
    void const set_ai_state(AIState new_state)              { m_ai_state      = new_state;            };
    void const set_position(glm::vec3 new_position)         { m_position      = new_position;         };
    void const set_movement(glm::vec3 new_movement)         { m_movement      = new_movement;         };
    void const set_velocity(glm::vec3 new_velocity)         { m_velocity      = new_velocity;         };
    void const set_speed(float new_speed)                   { m_speed         = new_speed;            };
    void const set_jumping_power(float new_jumping_power)   { m_jumping_power = new_jumping_power;   };
    void const set_acceleration(glm::vec3 new_acceleration) { m_acceleration  = new_acceleration;     };
    void const set_width(float new_width)                   { m_width         = new_width;            };
    void const set_height(float new_height)                 { m_height        = new_height;           };
};

