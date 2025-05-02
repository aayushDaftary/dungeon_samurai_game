#include "LevelC.h"
#include "Utility.h"
#define LEVELC_WIDTH 32
#define LEVELC_HEIGHT 35
//#define ENEMY_COUNT_B 3
#define ITEM_COUNT_C 6

unsigned int LEVELC_DATA[] =
{
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 7,
    7, 6, 6, 6, 6, 6, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 0, 0, 7,
    7, 6, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 0, 0, 7,
    7, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 7,
    7, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 7,
    7, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 0, 0, 7,
    7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 8, 9, 0, 0, 9, 9, 9, 9, 9, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 9, 8, 8, 9, 0, 0, 9, 8, 8, 8, 9, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 0, 0, 0, 0, 9, 8, 8, 8, 8, 9, 0, 0, 9, 8, 8, 9, 9, 9, 9, 8, 8, 8, 9, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 9, 9, 9, 9, 8, 8, 8, 8, 9, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 9, 8, 8, 9, 9, 8, 8, 9, 9, 9, 9, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 9, 9, 8, 8, 9, 9, 0, 0, 9, 8, 8, 9, 9, 8, 8, 9, 5, 5, 5, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 9, 8, 8, 9, 0, 0, 0, 9, 8, 8, 9, 9, 8, 8, 9, 5, 5, 5, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 9, 8, 8, 9, 9, 9, 9, 9, 8, 8, 9, 9, 8, 8, 9, 9, 9, 9, 9, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
    7, 9, 8, 8, 9, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7,
    7, 9, 8, 8, 9, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    7, 9, 8, 8, 9, 7, 10, 10, 5, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    7, 9, 8, 8, 8, 8, 10, 10, 5, 5, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    7, 9, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 7,
    7, 9, 9, 9, 9, 7, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    0, 0, 0, 0, 0, 7, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 5, 10, 7,
    0, 0, 0, 0, 0, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    0, 0, 0, 0, 0, 7, 10, 10, 10, 5, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    0, 0, 0, 0, 0, 7, 10, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    0, 0, 0, 0, 0, 7, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
    0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    
};

LevelC::~LevelC()
{
    delete[] m_game_state.enemies;
    delete[] m_game_state.items;
    delete m_game_state.player;
    delete m_game_state.map;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.heal_sfx);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelC::initialise(int lives)
{
    this->lives = lives;
    m_game_state.next_scene_id = -1;
    //m_game_state.player->magma_exposure = 0.0f;
    
    //GLuint grass_tex = Utility::load_texture("TX Tileset Grass.png");
    GLuint grass_tex = Utility::load_texture("basictiles.png");
    //GLuint wall_tex = Utility::load_texture("TX Tileset Wall.png");
    m_game_state.map = new Map(LEVELC_WIDTH, LEVELC_HEIGHT, LEVELC_DATA,grass_tex, 1.0f,8,15);

    m_game_state.player = new Entity();
    m_game_state.player->set_entity_type(PLAYER);
    m_game_state.player->on_magma = false;

    m_game_state.player->set_position(glm::vec3(3.0f, -3.0f, 0.0f));
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

    //hp and dmg
    m_game_state.player->m_health = 100;
    //sword damge
    m_game_state.player->m_damage = 10;
    m_game_state.player->m_base_speed = m_game_state.player->m_speed;
    m_game_state.player->m_base_damage = m_game_state.player->m_damage;

    // enemioes
    GLuint enemy_texture_id = Utility::load_texture("lowMonster.png");
    GLuint enemy1_texture_id = Utility::load_texture("lantern.png");
    GLuint sneaky_snake_texture_id = Utility::load_texture("snake.png");
    GLuint boss_texture_id = Utility::load_texture("boss_c_walk.png");
    GLuint boss_hit_texture_id = Utility::load_texture("boss_c_hit.png");
    GLuint boss_attack_left_texture_id  = Utility::load_texture("boss_c_attack_left.png");
    GLuint boss_attack_right_texture_id = Utility::load_texture("boss_c_attack_right.png");
    
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

    // vertical patrol 1
    m_game_state.enemies[0].set_entity_type(ENEMY);
    m_game_state.enemies[0].set_ai_type(VERTICAL_FLYER);
    m_game_state.enemies[0].set_ai_state(WALKING);
    m_game_state.enemies[0].m_texture_id = enemy_texture_id;
    m_game_state.enemies[0].set_position(glm::vec3(18.75f, -15.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[0].m_speed = 1.0f;
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[0].m_health = 30;
    m_game_state.enemies[0].m_damage = 20;

    //Vertical patrol 2
    m_game_state.enemies[1].set_entity_type(ENEMY);
    m_game_state.enemies[1].set_ai_type(VERTICAL_FLYER);
    m_game_state.enemies[1].set_ai_state(WALKING);
    m_game_state.enemies[1].m_texture_id = enemy_texture_id;
    m_game_state.enemies[1].set_position(glm::vec3(25.75f, -15.0f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[1].m_speed = 1.0f;
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].m_health = 30;
    m_game_state.enemies[1].m_damage = 20;

    //under health betwen vert patrols
    m_game_state.enemies[2].set_entity_type(ENEMY);
    m_game_state.enemies[2].set_ai_type(GUARD);
    m_game_state.enemies[2].set_ai_state(IDLE);
    m_game_state.enemies[2].m_texture_id = sneaky_snake_texture_id;
    m_game_state.enemies[2].set_position(glm::vec3(21.0f, -10.0f, 0.0f));
    m_game_state.enemies[2].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[2].m_speed = 1.5f;
    m_game_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[2].m_health = 30;
    m_game_state.enemies[2].m_damage = 20;
    
    //top right, hidden under health, snake texture REMINDER
    m_game_state.enemies[3].set_entity_type(ENEMY);
    m_game_state.enemies[3].set_ai_type(GUARD);
    m_game_state.enemies[3].set_ai_state(IDLE);
    m_game_state.enemies[3].m_texture_id = sneaky_snake_texture_id;
    m_game_state.enemies[3].set_position(glm::vec3(26.75f, -2.25f, 0.0f));
    m_game_state.enemies[3].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[3].m_speed = 1.5f;
    m_game_state.enemies[3].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[3].m_health = 30;
    m_game_state.enemies[3].m_damage = 20;
    
    //sneaky enemies below
    m_game_state.enemies[4].set_entity_type(ENEMY);
    m_game_state.enemies[4].set_ai_type(LURKER);
    m_game_state.enemies[4].set_ai_state(STATIONARY);
    m_game_state.enemies[4].m_texture_id = enemy1_texture_id;
    m_game_state.enemies[4].set_position(glm::vec3(7.0f, -11.0f, 0.0f));
    m_game_state.enemies[4].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[4].m_speed = 1.5f;
    m_game_state.enemies[4].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[4].m_health = 30;
    m_game_state.enemies[4].m_damage = 20;

    //sneaky
    m_game_state.enemies[5].set_entity_type(ENEMY);
    m_game_state.enemies[5].set_ai_type(LURKER);
    m_game_state.enemies[5].set_ai_state(STATIONARY);
    m_game_state.enemies[5].m_texture_id = enemy1_texture_id;
    m_game_state.enemies[5].set_position(glm::vec3(8.0f, -11.0f, 0.0f));
    m_game_state.enemies[5].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[5].m_speed = 1.5f;
    m_game_state.enemies[5].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[5].m_health = 30;
    m_game_state.enemies[5].m_damage = 25;
    
    //sneaky
    m_game_state.enemies[6].set_entity_type(ENEMY);
    m_game_state.enemies[6].set_ai_type(LURKER);
    m_game_state.enemies[6].set_ai_state(STATIONARY);
    m_game_state.enemies[6].m_texture_id = enemy1_texture_id;
    m_game_state.enemies[6].set_position(glm::vec3(9.0f, -11.0f, 0.0f));
    m_game_state.enemies[6].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[6].m_speed = 1.5f;
    m_game_state.enemies[6].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[6].m_health = 30;
    m_game_state.enemies[6].m_damage = 25;
    
    //snmeaky
    m_game_state.enemies[7].set_entity_type(ENEMY);
    m_game_state.enemies[7].set_ai_type(LURKER);
    m_game_state.enemies[7].set_ai_state(STATIONARY);
    m_game_state.enemies[7].m_texture_id = enemy1_texture_id;
    m_game_state.enemies[7].set_position(glm::vec3(9.0f, -12.0f, 0.0f));
    m_game_state.enemies[7].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[7].m_speed = 1.5f;
    m_game_state.enemies[7].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[7].m_health = 30;
    m_game_state.enemies[7].m_damage = 25;

    //Boss
    m_game_state.enemies[8].set_entity_type(ENEMY);
    m_game_state.enemies[8].set_ai_type(BOSS);
    m_game_state.enemies[8].set_ai_state(IDLE);
    m_game_state.enemies[8].m_animation_cols = 6;
    m_game_state.enemies[8].m_animation_rows = 1;
    m_game_state.enemies[8].m_animation_frames = 6;
    m_game_state.enemies[8].m_animation_indices = new int[6]{ 0, 1, 2, 3, 4, 5};
    m_game_state.enemies[8].m_walking[Entity::DOWN] = nullptr;
    m_game_state.enemies[8].m_walking[Entity::UP] = nullptr;
    m_game_state.enemies[8].m_walking[Entity::LEFT] = nullptr;
    m_game_state.enemies[8].m_walking[Entity::RIGHT] = nullptr;
    m_game_state.enemies[8].m_animation_index = 0;
    m_game_state.enemies[8].m_animation_time = 0.0f;
    m_game_state.enemies[8].m_texture_id = boss_texture_id;
    m_game_state.enemies[8].set_height(3.0f);
    m_game_state.enemies[8].set_width(3.0f);
    m_game_state.enemies[8].set_position(glm::vec3(18.0f, -30.0f, 0.0f));
    m_game_state.enemies[8].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[8].m_speed = 1.2f;
    m_game_state.enemies[8].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[8].m_health = 75;
    m_game_state.enemies[8].m_damage = 25;

    //boss getting hit
    
    m_game_state.enemies[8].m_hit_animation_cols = 4;
    m_game_state.enemies[8].m_hit_animation_rows = 1;
    m_game_state.enemies[8].m_hit_animation_frames = 4;
    m_game_state.enemies[8].m_hit_animation_indices = new int[4]{ 0, 1, 2, 3 };
    m_game_state.enemies[8].boss_hit_texture_id = boss_hit_texture_id;
    
    //boss attacking
    m_game_state.enemies[8].m_has_attack_sprites = true;
    
    m_game_state.enemies[8].m_attack_left_indices = new int[4]{ 0, 1, 2, 3 };
    m_game_state.enemies[8].m_attack_right_indices = new int[4]{ 0, 1, 2, 3 };
    m_game_state.enemies[8].boss_attack_left_texture_id = boss_attack_left_texture_id;
    m_game_state.enemies[8].boss_attack_right_texture_id = boss_attack_right_texture_id;
    
    m_number_of_items = ITEM_COUNT_C;
    m_game_state.items = new Entity[ITEM_COUNT_C];
    
    //between patrols
    GLuint medpack_texture_id = Utility::load_texture("medpack.png");
    m_game_state.items[0].set_entity_type(ITEM);
    m_game_state.items[0].m_texture_id = medpack_texture_id;
    m_game_state.items[0].item_type = Entity::MEDPACK;
    m_game_state.items[0].set_position(glm::vec3(21.0f, -10.0f, 0.0f));
    m_game_state.items[0].set_movement(glm::vec3(0.0f));
    m_game_state.items[0].m_speed = 0.0f;
    m_game_state.items[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.items[0].set_height(1.0f);
    m_game_state.items[0].set_width(1.0f);
    m_game_state.items[0].m_health = 0;
    m_game_state.items[0].m_damage = 0;
    
    //top right
    m_game_state.items[1].set_entity_type(ITEM);
    m_game_state.items[1].m_texture_id = medpack_texture_id;
    m_game_state.items[1].item_type = Entity::MEDPACK;
    m_game_state.items[1].set_position(glm::vec3(26.75f, -2.25f, 0.0f));
    m_game_state.items[1].set_movement(glm::vec3(0.0f));
    m_game_state.items[1].m_speed = 0.0f;
    m_game_state.items[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.items[1].set_height(1.0f);
    m_game_state.items[1].set_width(1.0f);
    m_game_state.items[1].m_health = 0;
    m_game_state.items[1].m_damage = 0;

    //guarded by lurkers
    m_game_state.items[2].set_entity_type(ITEM);
    m_game_state.items[2].m_texture_id = medpack_texture_id;
    m_game_state.items[2].item_type = Entity::MEDPACK;
    m_game_state.items[2].set_position(glm::vec3(8.0f, -12.0f, 0.0f));
    m_game_state.items[2].set_movement(glm::vec3(0.0f));
    m_game_state.items[2].m_speed = 0.0f;
    m_game_state.items[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.items[2].set_height(1.0f);
    m_game_state.items[2].set_width(1.0f);
    m_game_state.items[2].m_health = 0;
    m_game_state.items[2].m_damage = 0;
    
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

void LevelC::update(float delta_time)
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
                //door
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

        //if sword came in contact
        if (!player->m_hasHitThisSwing)
        {
            for (int i = 0; i < ENEMY_COUNT; i++)
            {
                Entity* enemy = &m_game_state.enemies[i];
                if (enemy->is_active() && m_sword->check_collision(enemy))
                {
                    enemy->m_health -= player->m_damage;
                    player->m_hasHitThisSwing = true;
                    if (enemy->get_ai_type() == BOSS)
                    {
                       enemy->m_is_hit = true;
                       enemy->m_animation_index = 0;
                       enemy->m_hit_animation_time = 0.0f;
                   }
                    if (enemy->m_health <= 0)
                    {
                        enemy->deactivate();
                    }
                    break;
                }
            }
        }

        m_sword->m_sword_timer += delta_time;
        if ( m_sword->m_sword_timer >= Entity::SWING_DURATION)
        {
            player->m_attacking = false;
            m_sword->m_sword_timer = 0.0f;
            //m_sword->set_position(glm::vec3(-100.0f,-100.0f,0.0f));
        }
    }

    //getss tileIndex that player is on
    float tx = (player->get_position().x + map->get_tile_size() * 0.5f)/ map->get_tile_size();
    float ty = -(player->get_position().y - map->get_tile_size() * 0.5f)/ map->get_tile_size();
    int tile_x = (int)floor(tx);
    int tile_y = (int)floor(ty);

    unsigned int tile = 0;
    if (tile_x >= 0 && tile_x < LEVELC_WIDTH && tile_y >= 0 && tile_y < LEVELC_HEIGHT)
    {
        tile = m_game_state.map->get_level_data()[tile_y * LEVELC_WIDTH + tile_x];
    }
    
    //magma
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
        if (player->magma_timer >= 0.2f)
        {
            player->m_health = std::max(0, player->m_health - 5);
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
            player->set_position(glm::vec3(3.0f, -3.0f, 0.0f));
        }
        else
        {
            m_game_state.next_scene_id = 1;
        }
    }
    
    bool boss_defeated = !m_game_state.enemies[8].is_active();
    static bool door_spawned = false;
    if (boss_defeated && !door_spawned)
    {
        door_spawned = true;
        Entity* door = &m_game_state.items[0];
        door->activate();
        door->set_entity_type(ITEM);
        door->item_type = Entity::DOOR;
        door->m_texture_id = Utility::load_texture("door.png");
        door->set_position(glm::vec3(15.0f, -32.0f, 0.0f));
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
            player->win_flag = true;
            m_game_state.next_scene_id = 0;
            door_spawned = false;
        }
    }
}

void LevelC::render(ShaderProgram* program)
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
        float t = sword->m_sword_timer/ Entity::SWING_DURATION;
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
