#include "Scene.h"
#include "Effects.h"
class LevelA : public Scene {
public:
    int ENEMY_COUNT = 3;
    Effects* m_effects;
    ~LevelA();

    void initialise(int lives) override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};
