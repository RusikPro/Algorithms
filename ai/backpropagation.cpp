#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Sigmoid activation function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of the sigmoid function.
// Note: Here the input 'x' is assumed to be already sigmoid(x).
double sigmoidDerivative(double x)
{
    return x * (1.0 - x);
}

// A simple neural network with one hidden layer
class NeuralNetwork
{
public:
    // Weights and biases for the network:
    // Input-to-hidden layer weights
    double w1, w2, w3, w4;
    // Hidden layer biases
    double b_h1, b_h2;
    // Hidden-to-output layer weights
    double w5, w6;
    // Output neuron bias
    double b_o;

    // Constructor: Initialize the network with fixed values (as in our numerical example)
    NeuralNetwork() {
        // Input-to-hidden layer
        w1 = 0.15;  // weight from x1 to hidden neuron h1
        w2 = 0.20;  // weight from x2 to hidden neuron h1
        w3 = 0.25;  // weight from x1 to hidden neuron h2
        w4 = 0.30;  // weight from x2 to hidden neuron h2
        b_h1 = 0.35;  // bias for hidden neuron h1
        b_h2 = 0.35;  // bias for hidden neuron h2

        // Hidden-to-output layer
        w5 = 0.40;  // weight from hidden neuron h1 to output neuron
        w6 = 0.45;  // weight from hidden neuron h2 to output neuron
        b_o = 0.60; // bias for the output neuron
    }

    // Structure to hold intermediate results from the forward pass.
    struct ForwardResult {
        double z_h1, a_h1; // Net input and activation for hidden neuron h1
        double z_h2, a_h2; // Net input and activation for hidden neuron h2
        double z_o, a_o;   // Net input and activation for the output neuron
    };

    // Performs the forward pass.
    // Given inputs x1 and x2, it computes the activations for the hidden and output layers.
    ForwardResult forward(double x1, double x2) {
        ForwardResult result;

        // ----- Hidden Layer -----
        // Compute net input for hidden neuron h1:
        // z_h1 = x1 * w1 + x2 * w2 + b_h1
        result.z_h1 = x1 * w1 + x2 * w2 + b_h1;
        // Apply sigmoid activation to obtain a_h1:
        result.a_h1 = sigmoid(result.z_h1);

        // Compute net input for hidden neuron h2:
        // z_h2 = x1 * w3 + x2 * w4 + b_h2
        result.z_h2 = x1 * w3 + x2 * w4 + b_h2;
        // Apply sigmoid activation to obtain a_h2:
        result.a_h2 = sigmoid(result.z_h2);

        // ----- Output Layer -----
        // Compute net input for the output neuron:
        // z_o = a_h1 * w5 + a_h2 * w6 + b_o
        result.z_o = result.a_h1 * w5 + result.a_h2 * w6 + b_o;
        // Apply sigmoid activation to get the final output a_o:
        result.a_o = sigmoid(result.z_o);

        return result;
    }

    // Trains the network on a single training example using backpropagation.
    // x1, x2: inputs; y: target output; learning_rate: step size for weight updates.
    void train(double x1, double x2, double y, double learning_rate) {
        // --- Forward Pass ---
        ForwardResult result = forward(x1, x2);

        // Compute the error (Mean Squared Error):
        // E = 1/2 * (y - a_o)^2
        double E = 0.5 * pow((y - result.a_o), 2);

        // --- Backward Pass ---
        // Compute the gradient for the output neuron using the chain rule.
        // The error E depends on a_o, which depends on z_o, which depends on the weights.
        // For example, for weight w5, the chain rule gives:
        // dE/dw5 = (dE/da_o) * (da_o/dz_o) * (dz_o/dw5)

        // Step 1: Compute dE/da_o.
        // Given E = 1/2*(y - a_o)^2, we have:
        // dE/da_o = a_o - y  (since the derivative of (y - a_o)^2 is -2*(y - a_o))
        double dE_da_o = result.a_o - y;

        // Step 2: Compute da_o/dz_o.
        // a_o = sigmoid(z_o), so da_o/dz_o = a_o*(1 - a_o)
        double da_o_dz_o = sigmoidDerivative(result.a_o);

        // Step 3: Combine to get the output delta:
        // delta_o = (a_o - y) * a_o*(1 - a_o)
        double delta_o = dE_da_o * da_o_dz_o;

        // Gradients for weights from hidden layer to output:
        // For w5: dz_o/dw5 = a_h1, so dE/dw5 = delta_o * a_h1
        double dE_dw5 = delta_o * result.a_h1;
        // For w6: dz_o/dw6 = a_h2, so dE/dw6 = delta_o * a_h2
        double dE_dw6 = delta_o * result.a_h2;
        // Gradient for output bias b_o is simply delta_o.
        double dE_db_o = delta_o;

        // --- Backpropagation to the Hidden Layer ---
        // For each hidden neuron, we compute its delta (error term) as:
        // delta_h = (delta_o * weight_to_output) * sigmoid'(z_h)
        // Hidden neuron h1:
        double da_h1_dz_h1 = sigmoidDerivative(result.a_h1); // derivative of activation for h1
        double delta_h1 = da_h1_dz_h1 * (delta_o * w5);         // error contribution from h1

        // Hidden neuron h2:
        double da_h2_dz_h2 = sigmoidDerivative(result.a_h2); // derivative of activation for h2
        double delta_h2 = da_h2_dz_h2 * (delta_o * w6);         // error contribution from h2

        // Gradients for weights from input layer to hidden layer:
        // For w1 (from x1 to h1): dE/dw1 = delta_h1 * x1
        double dE_dw1 = delta_h1 * x1;
        // For w2 (from x2 to h1): dE/dw2 = delta_h1 * x2
        double dE_dw2 = delta_h1 * x2;
        // For w3 (from x1 to h2): dE/dw3 = delta_h2 * x1
        double dE_dw3 = delta_h2 * x1;
        // For w4 (from x2 to h2): dE/dw4 = delta_h2 * x2
        double dE_dw4 = delta_h2 * x2;
        // Gradients for hidden biases:
        double dE_db_h1 = delta_h1;
        double dE_db_h2 = delta_h2;

        // --- Weight Update ---
        // Update each weight and bias by subtracting the learning rate multiplied by its gradient.
        w5 -= learning_rate * dE_dw5;
        w6 -= learning_rate * dE_dw6;
        b_o -= learning_rate * dE_db_o;

        w1 -= learning_rate * dE_dw1;
        w2 -= learning_rate * dE_dw2;
        w3 -= learning_rate * dE_dw3;
        w4 -= learning_rate * dE_dw4;
        b_h1 -= learning_rate * dE_db_h1;
        b_h2 -= learning_rate * dE_db_h2;

        // Optionally, print the error to monitor training progress.
        // cout << "Training error: " << E << endl;
    }
};

int main() {
    // Set numeric precision for better readability of outputs
    cout << fixed << setprecision(5);

    // Create an instance of the NeuralNetwork.
    NeuralNetwork nn;

    // Define a single training example:
    // Inputs:
    double x1 = 0.05;
    double x2 = 0.10;
    // Target output:
    double target = 0.001;

    NeuralNetwork::ForwardResult initialResult = nn.forward(x1, x2);
    cout << "\\Initial output before training: " << initialResult.a_o << endl;

    // Define the learning rate
    double learning_rate = 0.5;

    // Number of training iterations (epochs)
    int epochs = 5000000;

    // Training loop: update weights using backpropagation over many iterations
    for (int i = 0; i < epochs; ++i) {
        nn.train(x1, x2, target, learning_rate);

        // Optionally, every 1000 epochs, display the network's output for monitoring.
        if (i % 10000 == 0) {
            NeuralNetwork::ForwardResult result = nn.forward(x1, x2);
            cout << "Epoch " << i << " - Output: " << result.a_o << endl;
        }
    }

    // After training, display the final output of the network for the training example.
    NeuralNetwork::ForwardResult finalResult = nn.forward(x1, x2);
    cout << "\nFinal output after training: " << finalResult.a_o << endl;

    return 0;
}
