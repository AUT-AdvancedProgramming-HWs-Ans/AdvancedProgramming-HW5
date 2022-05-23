#include "espresso_based.h"

EspressoBased::EspressoBased()
    : name { "EspressoBased" }
    , ingredients {}
{

    /**
     * @brief Default constructor
     */
}

EspressoBased::EspressoBased(const EspressoBased& esp)
    : name { esp.name }
    , ingredients {}
{

    /**
     * @brief Copy constructor
     *
     * @param esp
     */

    for (const auto& i : esp.ingredients) {

#define INGREDIENTS(Name)       \
    if (i->get_name() == #Name) \
        ingredients.push_back(new Name { i->get_units() });

        INGREDIENTS(Cinnamon);
        INGREDIENTS(Chocolate);
        INGREDIENTS(Sugar);
        INGREDIENTS(Cookie);
        INGREDIENTS(Espresso);
        INGREDIENTS(Milk);
        INGREDIENTS(MilkFoam);
        INGREDIENTS(Water);
    }
}

EspressoBased::~EspressoBased()
{
    /**
     * @brief Destructor
     */
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

void EspressoBased::operator=(const EspressoBased& esp)
{
    /**
     * @brief Assignment operator
     *
     * @param esp
     */
    if (this != &esp) {
        name = esp.name;

        for (auto& i : ingredients)
            delete i;
        ingredients.clear();

        for (const auto& i : esp.ingredients) {

#define INGREDIENTS(Name)       \
    if (i->get_name() == #Name) \
        ingredients.push_back(new Name { i->get_units() });

            INGREDIENTS(Cinnamon);
            INGREDIENTS(Chocolate);
            INGREDIENTS(Sugar);
            INGREDIENTS(Cookie);
            INGREDIENTS(Espresso);
            INGREDIENTS(Milk);
            INGREDIENTS(MilkFoam);
            INGREDIENTS(Water);
        }
    }
}

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
    /**
     * @brief Getter for ingredients
     *
     * @return std::vector<Ingredient*>&
     */
    return ingredients;
}
