#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
#include "projeor.h"


int main() {
	string main_file= "diabetes.csv";
	string train_file="diabetes_train_file.csv";
	string test_file= "diabetes_test_file.csv";
	double split_ratio= 0.3;


	split_data(main_file, train_file, test_file,split_ratio);

	vector<Patient> train_patients;
	readDataFromFile(train_file, train_patients);

//	printDataOfCouple(train_patients, 1);

	vector<Patient> test_patients;
	readDataFromFile(test_file, test_patients);

	// printDataOfCouple(test_patients, 0);

	vector<bool> predictions, true_labels;
	get_true_labels(test_patients, true_labels);
	// Perform classification with kNN
	int k = 5;
	kNN_algoritma(train_patients, test_patients, predictions, k);
	prent_preds_true_labels(true_labels,predictions,test_patients.size());
	int oran = compute_accuracy(predictions,true_labels);
	cout<< "oran\n: "<<oran;
return 0;
}

