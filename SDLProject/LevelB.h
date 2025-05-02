#include "Scene.h"
#include "Effects.h"
class LevelB : public Scene {
public:
    int ENEMY_COUNT = 9;
    Effects* m_effects;
    ~LevelB();

    void initialise(int lives) override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};
