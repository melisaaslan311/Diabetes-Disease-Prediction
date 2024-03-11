#include "projeor.h"
#include "string"
using namespace std;
void split_data(string main_file,string train_file,string test_file,double split_ratio){
	srand(time(0));
	ifstream dosyaokuyucu;
	ofstream dosyayazici_test,dosyayazici_train;
	dosyaokuyucu.open(main_file);
	if(dosyaokuyucu){
		string ilksatir, datasatiri;
		getline(dosyaokuyucu, ilksatir);
		dosyayazici_train.open(train_file);
		dosyayazici_test.open(test_file);
		dosyayazici_train<< ilksatir<< endl;
		dosyayazici_test<< ilksatir<< endl;
		while(getline(dosyaokuyucu, datasatiri)){
			if(rand()%100> split_ratio*100){
				dosyayazici_train<< datasatiri<< endl;
			}else{
				dosyayazici_test<< datasatiri<< endl;
			}

	}
	dosyayazici_train.close();
	dosyayazici_test.close();
	dosyaokuyucu.close();
	}else{
		cout<<"dosya okunamadi";

	}

	}

void printDataOfCouple(vector<Patient> patients, int index){

	cout<< "diabetes:"<< patients[index].diabetes<< endl;
	cout<< "answers:"<< endl;
	for(int i=0; i< patients[index].ozellik.size();i++){
		cout<< patients[index].ozellik[i]<< ",";
	}
}

void satirlarabol(string satir,vector<int>&ozellik, bool&diabetes){
	int pos_r=satir.find('\r');
	int pos_n= satir.find('\n');
	int pos= max(pos_r, pos_n);
	if(pos>0){
		satir= satir.substr(0,pos);
	}
	diabetes= (satir[satir.length()-1]=='1');
	satir= satir.substr(0, satir.length()-1);
	stringstream ss(satir);
	string parcalar;
	while(getline(ss,parcalar,',')){
		ozellik.push_back(stoi(parcalar));

	}

}

void readDataFromFile(string filename, vector<Patient> & patients){
	ifstream dosyaokuyucu;
	int satir_endeksi=0;
	string satir;
	dosyaokuyucu.open(filename);
	if(dosyaokuyucu){
		while(getline(dosyaokuyucu,satir)){
			if(satir_endeksi>0){
				Patient patien;
				satirlarabol(satir, patien.ozellik, patien.diabetes);
				patients.push_back(patien);
			}
	satir_endeksi++;
	}dosyaokuyucu.close();
	}else{
		cout<< filename<< "okunamadi";
	}

}

void get_true_labels(vector<Patient >test_patients, vector<bool> & true_labels){
	for(size_t i=0;i < test_patients.size();i++){
		true_labels.push_back(test_patients[i].diabetes);
	}
}

double manhattan(vector<int> x,vector<int> y){
	double toplam = 0;
	for(int i =0;i <x.size();i++){
		toplam += abs(x[i]-y[i]);
	}
	return toplam;
}

void swap(vector<double>& vect, vector<size_t> &indexler,int ilk,int son){
				int temp= vect[ilk];
				vect[ilk]=vect[son];
				vect[son]=temp;

				int temp1=indexler[ilk];
				indexler[ilk]=indexler[son];
				indexler[son]=temp1;

}
void kNN_algoritma(vector<Patient> train_patients, vector<Patient> test_patients, vector<bool> & predictions, int k){
	vector<size_t> indexler;
	for(int i =0; i<test_patients.size();i++){
		vector<double> farklar;
		for(int j =0;j< train_patients.size();j++){
			double fark = manhattan(test_patients[i].ozellik,train_patients[j].ozellik);
			farklar.push_back(fark);
			indexler.push_back(j);
		}
		for(int k=0;k<farklar.size();k++){
			for(int m=0;m <farklar.size()-1;m++){
				if(farklar[m]>farklar[m-1]){
					swap(farklar,indexler,m,m+1);
				}
			}
		}
//		for(int t=0;t <farklar.size();t++){
//			cout<<farklar[t]<<" "<<indexler[t]<<endl;
//		}
//		cout<<"******"<<endl;
		int top=0;
		int u=0;
		while(u<k){
			top+=train_patients[indexler[u]].diabetes;
			u++;
		}
		if(top>=3){
			predictions.push_back(1);
		}else{
			predictions.push_back(0);
		}
		farklar.clear();
		indexler.clear();

	}
}
int compute_accuracy(vector<bool>predictions, vector<bool>true_labels){
	int dogrutahmin=0;
	int yanlistahmin=0;
	for(int i=0;i<true_labels.size();i++){
		if(predictions[i]==true_labels[i]){
			dogrutahmin++;
		}else{
			yanlistahmin++;
		}
	}
	int orani=(100*dogrutahmin)/(dogrutahmin+yanlistahmin);
	return orani;

}
void prent_preds_true_labels(vector<bool>true_labels,vector<bool>predictions,size_t num_samp){
	cout<<"true_labels: "<<"\t";
	for(int i=0;i <num_samp;i++){
		cout<<true_labels[i];
	}
	cout<<endl;
	cout<<"predictions:"<<"\t";
	for(int i=0;i <num_samp;i++){
		cout<<predictions[i];
}
}

