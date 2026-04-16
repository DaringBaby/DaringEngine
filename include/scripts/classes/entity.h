#include "SDL3/SDL_render.h"
#include <string>

class Entity {
    private:
        int id;
        float pos_x;
        float pos_y;
        float size_x;
        float size_y;
        bool moving = false;
        float target_x = 0;
        float target_y = 0;
        int current_dir = 0;
        std::string image_path;
        SDL_Surface* surface;
        SDL_Texture* texture;
    public:
        Entity(int id, float pos_x, float pos_y, float size_x, float size_y, std::string image_path, SDL_Renderer* renderer);
        Entity() : id(0), pos_x(0), pos_y(0), size_x(32), size_y(32), image_path("0"), surface(nullptr), texture(nullptr) {};
        void set_id(int id);
        void set_moving(bool mov);
        void set_pos(float pos_x, float pos_y);
        void set_pos_x(float pos_x);
        void set_pos_y(float pos_y);
        void set_size(float size_x, float size_y);
        void set_target_x(float tx);
        void set_target_y(float ty);
        void set_current_dir(int dir);
        int get_id();
        bool get_moving();
        float get_pos_x();
        float get_pos_y();
        float get_size_x();
        float get_size_y();
        float get_target_x();
        float get_target_y();
        int get_current_dir();
        void render(SDL_Renderer* renderer);
};
