#include <SDL3/SDL.h>
#include "scripts/classes/entity.h"

Entity::Entity(int id, float pos_x, float pos_y, float size_x, float size_y, std::string image_path, SDL_Renderer* renderer) {
    this->id = id;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->size_x = size_x;
    this->size_y = size_y;
    this->image_path = image_path;
    this->surface = SDL_LoadBMP(this->image_path.c_str());
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    return;
}

void Entity::render(SDL_Renderer* renderer) {
    SDL_FRect destRect = { this->pos_x, this->pos_y, this->size_x, this->size_y };
    SDL_RenderTexture(renderer, texture, NULL, &destRect);
}

int Entity::get_id() {
    return this->id;
}

float Entity::get_pos_x() {
    return this->pos_x;
}

float Entity::get_pos_y() {
    return this->pos_y;
}

void Entity::set_id(int id) {
    this->id = id;
}

void Entity::set_pos_x(float x) {
    this->pos_x = x;
}

void Entity::set_pos_y(float y) {
    this->pos_y = y;
}
