# P4: Greedy (fractional) knapsack

def fractional_knapsack(items, capacity):
    # Each item is (value, weight); sort by descending value/weight ratio.
    items = sorted(items, key=lambda item: item[0] / item[1], reverse=True)
    total_value = 0.0
    chosen = []

    for value, weight in items:
        if capacity == 0:
            break
        taken_weight = min(weight, capacity)
        fraction = taken_weight / weight
        total_value += value * fraction
        chosen.append((value, weight, fraction))
        capacity -= taken_weight

    return total_value, chosen


n = int(input("Enter number of items: "))
items = []
for i in range(n):
    value, weight = map(float, input(
        f"Enter value and weight of item {i + 1}: ").split())
    if weight <= 0:
        raise ValueError("Weight must be positive.")
    items.append((value, weight))

capacity = float(input("Enter knapsack capacity: "))
if capacity < 0:
    raise ValueError("Capacity cannot be negative.")

max_value, chosen = fractional_knapsack(items, capacity)
print("Items taken (value, weight, fraction):")
for item in chosen:
    print(f"{item[0]:g}, {item[1]:g}, {item[2]:.2f}")
print(f"Maximum value: {max_value:.2f}\n")
