import csv
import json
import sys


def load_data():
    miles = []
    prices = []

    try:
        with open("data.csv", "r") as f:
            reader = csv.reader(f)
            next(reader)

            for row in reader:
                if len(row) != 2:
                    continue
                try:
                    miles.append(float(row[0]))
                    prices.append(float(row[1]))
                except ValueError:
                    continue

    except FileNotFoundError:
        return [], []

    return miles, prices


def load_model():
    try:
        with open("model.json", "r") as f:
            model = json.load(f)
            return model["theta0"], model["theta1"]
    except (FileNotFoundError, json.JSONDecodeError, KeyError):
        print("Error: model.json missing or invalid. Run train.py first.")
        sys.exit(1)


def estimate_price(mileage, theta0, theta1):
    return theta0 + theta1 * mileage


def compute_precision(miles, prices, theta0, theta1):
    m = len(miles)

    predictions = [estimate_price(x / 100000, theta0, theta1) for x in miles]
    mae = sum(abs(predictions[i] - prices[i]) for i in range(m)) / m

    mse = sum((predictions[i] - prices[i]) ** 2 for i in range(m)) / m
    rmse = mse ** 0.5

    mean_price = sum(prices) / m
    ss_res = sum((prices[i] - predictions[i]) ** 2 for i in range(m))
    ss_tot = sum((prices[i] - mean_price) ** 2 for i in range(m))
    r2 = 1 - (ss_res / ss_tot) if ss_tot != 0 else 0

    return mae, rmse, r2


def main():
    miles, prices = load_data()

    if len(miles) == 0:
        print("Error: data.csv is empty or invalid.")
        return

    theta0, theta1 = load_model()

    mae, rmse, r2 = compute_precision(miles, prices, theta0, theta1)

    print(f"Model: price = {theta0:.2f} + {theta1:.2f} * (mileage / 100000)")
    print(f"Mean Absolute Error (MAE) : {mae:.2f}")
    print(f"Root Mean Squared Error (RMSE) : {rmse:.2f}")
    print(f"R^2 score : {r2:.4f}  (closer to 1 = better fit)")


if __name__ == "__main__":
    main()
