#include "SDL3/SDL_render.h"
#include <string>

class Entity {
    private:
        int id;
        float pos_x;
        float pos_y;
        float size_x;
        float size_y;
        std::string image_path;
        SDL_Surface* surface;
        SDL_Texture* texture;
    public:
        Entity(int id, float pos_x, float pos_y, float size_x, float size_y, std::string image_path, SDL_Renderer* renderer);
        void set_id(int id);
        void set_pos(float pos_x, float pos_y);
        void set_pos_x(float pos_x);
        void set_pos_y(float pos_y);
        void set_size(float size_x, float size_y);
        int get_id();
        float get_pos_x();
        float get_pos_y();
        float get_size_x();
        float get_size_y();
        void render(SDL_Renderer* renderer);
};
