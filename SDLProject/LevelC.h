#include "Scene.h"
#include "Effects.h"
class LevelC : public Scene {
public:
    int ENEMY_COUNT = 9;
    Effects* m_effects;
    ~LevelC();

    void initialise(int lives)override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};
