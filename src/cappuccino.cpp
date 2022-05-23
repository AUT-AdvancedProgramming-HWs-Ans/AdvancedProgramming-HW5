#include "cappuccino.h"

Cappuccino::Cappuccino()
    : EspressoBased()
    , side_items {}
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
    : EspressoBased { cap }
{
    /**
     * @brief Copy constructor
     */

    for (const auto& i : cap.side_items) {
#define SIDE_ITEM(Name)         \
    if (i->get_name() == #Name) \
        side_items.push_back(new Name { i->get_units() });

        SIDE_ITEM(Cinnamon);
        SIDE_ITEM(Chocolate);
        SIDE_ITEM(Sugar);
        SIDE_ITEM(Cookie);
        SIDE_ITEM(Espresso);
        SIDE_ITEM(Milk);
        SIDE_ITEM(MilkFoam);
        SIDE_ITEM(Water);
    }
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
        side_items.clear();

        for (const auto& i : cap.side_items) {
#define SIDE_ITEM(Name)         \
    if (i->get_name() == #Name) \
        side_items.push_back(new Name { i->get_units() });

            SIDE_ITEM(Cinnamon);
            SIDE_ITEM(Chocolate);
            SIDE_ITEM(Sugar);
            SIDE_ITEM(Cookie);
            SIDE_ITEM(Espresso);
            SIDE_ITEM(Milk);
            SIDE_ITEM(MilkFoam);
            SIDE_ITEM(Water);
        }
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
    for (const auto& i : ingredients)
        price += i->price();

    for (const auto& i : side_items)
        price += i->price();

    return price;
}

void Cappuccino::add_side_item(Ingredient* side)
{
    /**
     * @brief Add a side item
     *
     * @param side
     */
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items()
{
    /**
     * @brief Get the side items object
     *
     * @return std::vector<Ingredient*>&
     */
    return side_items;
}