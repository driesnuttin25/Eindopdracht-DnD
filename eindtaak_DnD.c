#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int main() {
    struct Spell {
        char* index;
        char* name;
        char* url;
        char** desc;
        char** higher_level;
        char* range;
        enum Component {
            V,
            S,
            M
        }* components;
        char* material;
        struct AreaOfEffect {
            int size;
            enum Type {
                sphere,
                cone,
                cylinder,
                line,
                cube
            } type;
        } area_of_effect;
        bool ritual;
        char* duration;
        bool concentration;
        char* casting_time;
        int level;
        char* attack_type;
        union Damage {
            struct DamageAtCharacterLevel {
                void* damage_at_character_level;
            } at_character_level;
            struct DamageAtSlotLevel {
                void* damage_at_slot_level;
            } at_slot_level;
            struct DamageType {
                char* index;
                char* name;
                char* url;
            } type;
        } damage;
        struct School {
            char* index;
            char* name;
            char* url;
        } school;
        struct Class {
            char* index;
            char* name;
            char* url;
        }* classes;
        struct Subclass {
            char* index;
            char* name;
            char* url;
        }* subclasses;
    };

    return 0;
}
