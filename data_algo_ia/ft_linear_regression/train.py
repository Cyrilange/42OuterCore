import csv
import json
import matplotlib.pyplot as plt


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


def train(miles, prices, lr, iterations):
    theta0 = 0
    theta1 = 0
    m = len(miles)

    for _ in range(iterations):
        sum_error = 0
        sum_error_x = 0

        for i in range(m):
            pred = theta0 + theta1 * miles[i]
            error = pred - prices[i]
            sum_error += error
            sum_error_x += error * miles[i]

        tmp0 = lr * (1/m) * sum_error
        tmp1 = lr * (1/m) * sum_error_x

        theta0 -= tmp0
        theta1 -= tmp1

    return theta0, theta1


def save_model(theta0, theta1):
    with open("model.json", "w") as f:
        json.dump({"theta0": theta0, "theta1": theta1}, f)


def plot_result(miles_raw, prices, theta0, theta1):
    plt.scatter(miles_raw, prices, color="steelblue", label="Data")

    x_line = [min(miles_raw), max(miles_raw)]
    y_line = [theta0 + theta1 * (x / 100000) for x in x_line]
    plt.plot(x_line, y_line, color="pink", label="Fitted Line")

    plt.xlabel("Km")
    plt.ylabel("Price")
    plt.legend()
    plt.savefig("training_result.png")
    print("Graph saved as training_result.png")


def main():
    miles_raw, prices = load_data()

    if len(miles_raw) == 0 or len(prices) == 0:
        print("Error: data.csv is empty or invalid.")
        return

    miles = [x / 100000 for x in miles_raw]

    lr = 0.01
    it = 5000

    theta0, theta1 = train(miles, prices, lr, it)

    save_model(theta0, theta1)
    print("Training done")

    plot_result(miles_raw, prices, theta0, theta1)


if __name__ == "__main__":
    main()
