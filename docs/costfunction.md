# Calculating the cost of a prediction in Machine learning
When performing machine learning, you train the machine by continously supplying it with training data.
The machine makes a prediction, and must then determine how different from the training data it is.

To determine this difference/ error margin, we use a cost function.
There are a number of different cost functions, but the one used in our project is the Mean Squared Error (MSE) function.

MSE is quite simply a summation of the squared difference (the length of the vector) between our target values and the predicted values.

The MSE is then used to train the model, by attempting to reduce the cost/error as much as possible.

When fully writing this section, be sure to include some nice math.
