import json
import os
import sys
from train import load_data

def load_model():
    if not os.path.exists("model.json"):
        return 0.0, 0.0

    with open("model.json", "r") as f:
        content = f.read().strip()

        if not content:
            print("Error: model.json is empty. Train first.")
            sys.exit(1)

        try:
            model = json.loads(content)
        except json.JSONDecodeError:
            print("Error: model.json is corrupted.")
            sys.exit(1)

    return model["theta0"], model["theta1"]


def estimate_price(mileage, theta0, theta1):
    return theta0 + theta1 * mileage

def ft_sum(numbers) -> float:
    total = 0

    for number in numbers:
        total += number

    return total

def ft_abs(n: int) -> int:
    return -n if n < 0 else n

def ft_len(numbers: list) -> int:
    count = 0

    for element in numbers:
        count += 1

    return count


def compute_precision(miles, prices, theta0, theta1):
    m = ft_len(miles)

    predictions = [estimate_price(x / 100000, theta0, theta1) for x in miles]

    mae = ft_sum(ft_abs(predictions[i] - prices[i]) for i in range(m)) / m

    mse = ft_sum((predictions[i] - prices[i]) ** 2 for i in range(m)) / m
    rmse = mse ** 0.5

    mean_price = ft_sum(prices) / m
    ss_res = ft_sum((prices[i] - predictions[i]) ** 2 for i in range(m))
    ss_tot = ft_sum((prices[i] - mean_price) ** 2 for i in range(m))
    r2 = 1 - (ss_res / ss_tot) if ss_tot != 0 else 0

    return mae, rmse, r2


def get_mileage():
    while True:
        try:
            mileage = float(input("Enter mileage: "))
            if mileage < 0:
                print("Error: mileage must be positive")
                continue
            return mileage
        except ValueError:
            print("Error: invalid input, please enter a number")


def main():
    theta0, theta1 = load_model()

    miles, prices = load_data()

    mae, rmse, r2 = compute_precision(
        miles, prices, theta0, theta1
    )

    print(f"MAE: {mae:.2f}")
    print(f"RMSE: {rmse:.2f}")
    print(f"R²: {r2:.2f}")

    mileage = get_mileage() / 100000

    price = estimate_price(mileage, theta0, theta1)

    if price < 0:
        print("Estimated price: 0 (price cannot be negative)")
    elif price == 0:
        print("Estimated price: 0")
    else:
        print(f"Estimated price: {price:.2f}")

if __name__ == "__main__":
    main()
