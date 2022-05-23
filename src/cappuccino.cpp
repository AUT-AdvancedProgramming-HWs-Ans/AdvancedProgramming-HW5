#include "cappuccino.h"

Cappuccino::Cappuccino()
{
    /**
     * @brief Default constructor
     */
    name = "Cappuccino";
    ingredients.push_back(new Espresso { 2 });
    ingredients.push_back(new Milk { 2 });
    ingredients.push_back(new MilkFoam { 1 });
}

Cappuccino::Cappuccino(const Cappuccino& cap)
    : EspressoBased(cap)
{
    /**
     * @brief Copy constructor
     */
}

Cappuccino::~Cappuccino()
{
    /**
     * @brief Construct a new for object
     *
     * @param side_items
     */

    for (const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap)
{
    /**
     * @brief Assignment operator
     *
     * @param cap
     */
    if (this != &cap) {
        name = cap.name;
        ingredients = cap.ingredients;
    }
}

std::string Cappuccino::get_name()
{
    /**
     * @brief Get the name object
     *
     * @return std::string
     */
    // std::cout<< this->name << std::endl;
    return name;
}

double Cappuccino::price()
{
    /**
     * @brief Get the price object
     *
     * @return double
     */
    double price {};
    for (const auto& i : side_items)
        price += i->price();
    return price;
}