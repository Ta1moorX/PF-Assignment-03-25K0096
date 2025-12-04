#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    // Base case: fuel exhausted
    if (fuel <= 0)
    {
        printf("\nMission Failed! Fuel exhausted at Planet %d\n", planet - 1);
        return 0;
    }
    // Base case: all planets visited successfully
    if (planet > totalPlanets)
    {
        printf("\nMission Successful! Journey completed with %d fuel remaining\n", fuel);
        return 1;
    }
    fuel = fuel - consumption;

    fuel = fuel + recharge;

    if (planet % 4 == 0)
    {
        fuel = fuel + solarBonus;
        printf("Planet %d: Fuel Remaining = %d (Solar Recharge Applied!)\n", planet, fuel);
    }
    else
    {
        printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    }
    // Recursive case: move to next planet
    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}
int main()
{
    int initialFuel = 500;
    int consumption = 80;
    int recharge = 30;
    int solarBonus = 100;
    int totalPlanets = 10;

    printf("Spacecraft Fuel Simulation:\n");
    printf("Initial Fuel: %d\n", initialFuel);
    printf("Consumption per planet: %d\n", consumption);
    printf("Recharge per planet: %d\n", recharge);
    printf("Solar bonus (every 4th planet): %d\n", solarBonus);
    printf("Total planets: %d\n\n", totalPlanets);

    calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}