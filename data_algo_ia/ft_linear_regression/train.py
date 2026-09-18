import csv
import json
import matplotlib.pyplot as plt


def load_data() -> tuple[list[float], list[float]]:
    """
    Load mileage and price data from the CSV file.

    The CSV file must contain two columns: mileage and price.
    Invalid rows and values that cannot be converted to floats
    are ignored.

    :return: A tuple containing the list of mileages and the list
        of corresponding prices.
    :rtype: tuple[list[float], list[float]]
    """
    miles: list[float] = []
    prices: list[float] = []

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


def train( miles: list[float], prices: list[float], lr: float, iterations: int ) -> tuple[float, float]:
    """
    Train the linear regression model using gradient descent.

    :param miles: Normalized mileage values used as input data.
    :param prices: Price values corresponding to each mileage.
    :param lr: Learning rate used to update the model parameters.
    :param iterations: Number of gradient descent iterations.
    :return: A tuple containing theta0 and theta1, the trained
        linear regression parameters.
    :rtype: tuple[float, float]
    """
    theta0: float = 0
    theta1: float = 0
    m: int = len(miles)

    for _ in range(iterations):
        sum_error: float = 0
        sum_error_x: float = 0

        for i in range(m):
            pred: float = theta0 + theta1 * miles[i]
            error: float = pred - prices[i]
            sum_error += error
            sum_error_x += error * miles[i]

        tmp0: float = lr * (1/m) * sum_error
        tmp1: float = lr * (1/m) * sum_error_x

        theta0 -= tmp0
        theta1 -= tmp1

    return theta0, theta1


def save_model(theta0: float, theta1: float) -> None:
    """
    Save the trained model parameters to a JSON file.

    :param theta0: Intercept parameter of the linear regression model.
    :param theta1: Slope parameter of the linear regression model.
    :return: None
    :rtype: None
    """
    with open("model.json", "w") as f:
        json.dump({"theta0": theta0, "theta1": theta1}, f)


def ft_max(n: list[float]) -> float:
    """
    Find the maximum value in a list of floats.

    :param n: List of floating-point numbers.
    :return: The largest value contained in the list.
    :rtype: float
    """
    maximum: float = n[0]

    for number in n:
        if number > maximum:
            maximum = number

    return maximum


def ft_min(n: list[float]) -> float:
    """
    Find the minimum value in a list of floats.

    :param n: List of floating-point numbers.
    :return: The smallest value contained in the list.
    :rtype: float
    """
    minimum: float = n[0]

    for number in n:
        if number < minimum:
            minimum = number

    return minimum


def plot_result( miles_raw: list[float], prices: list[float], theta0: float, theta1: float ) -> None:
    """
    Plot the training data and the fitted linear regression line.

    The resulting graph is saved as ``training_result.png``.

    :param miles_raw: Original, non-normalized mileage values.
    :param prices: Price values corresponding to the mileage data.
    :param theta0: Intercept parameter of the trained model.
    :param theta1: Slope parameter of the trained model.
    :return: None
    :rtype: None
    """
    plt.scatter(miles_raw, prices, color="steelblue", label="Data")

    x_line: list[float] = [ft_min(miles_raw), ft_max(miles_raw)]
    y_line: list[float] = [theta0 + theta1 * (x / 100000) for x in x_line]
    plt.plot(x_line, y_line, color="pink", label="Fitted Line")

    plt.xlabel("Km")
    plt.ylabel("Price")
    plt.legend()
    plt.savefig("training_result.png")
    print("Graph saved as training_result.png")


def main() -> None:
    """
    Execute the complete training process.

    The function loads the dataset, normalizes the mileage values,
    trains the linear regression model, saves the trained parameters,
    and generates a graph containing the training data and fitted line.

    :return: None
    :rtype: None
    """
    miles_raw: list[float]
    prices: list[float]

    miles_raw, prices = load_data()

    if len(miles_raw) == 0 or len(prices) == 0:
        print("Error: data.csv is empty or invalid.")
        return

    miles: list[float] = [x / 100000 for x in miles_raw]

    lr: float = 0.01
    it: int = 10000

    theta0: float
    theta1: float

    theta0, theta1 = train(miles, prices, lr, it)

    save_model(theta0, theta1)
    print("Training done")

    plot_result(miles_raw, prices, theta0, theta1)


if __name__ == "__main__":
    main()
