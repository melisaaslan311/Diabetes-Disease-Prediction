#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
using namespace std;
#ifndef PROJEOR_H_
#define PROJEOR_H_

class Patient{
public:
	bool diabetes;
	vector<int> ozellik;
};

void split_data(string ,string ,string,double );
void readDataFromFile(string filename, vector<Patient> & patients);
void printDataOfCouple(vector<Patient> patients, int ind);
void get_true_labels(vector<Patient >test_patients, vector<bool> &true_labels);
double manhattan(vector<int> x,vector<int> y);
void swap(vector<double> &vect, vector<size_t> &indexler,int ilk,int son);
void kNN_algoritma(vector<Patient> train_patients, vector<Patient> test_patients, vector<bool> & predictions, int k);
void prent_preds_true_labels(vector<bool>true_labels,vector<bool>predictions,size_t num_samp);
int compute_accuracy(vector<bool>predictions, vector<bool>true_labels);
#endif /* PROJEOR_H_ */
