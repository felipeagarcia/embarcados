#include <stdio.h>

#define NUM_ROWS 192
#define NUM_COLS 57

typedef struct Perceptron{
	int inputs_qtd;
	float *weights;
	float bias;
}Perceptron;


int recognize(Perceptron p, float *data, int batch_size);

void train_perceptron(Perceptron *p, float **data, int num_epochs, float learn_rate);

int step_function(float x);


int main(){
    int epochs = 2000, i, j;
    float learn_rate = 0.01;
    Perceptron p;
    p.inputs_qtd = 48;
    p.weights = (float*) malloc (p.inputs_qtd * sizeof(float));
    FILE* db = fopen("dBtrGr4St1.dat", "r");
    if(db == NULL){
        printf("Error");
    }
    FILE* dbt = fopen("dBtestGr4St1.dat", "r");
    float **data = (float**)malloc(NUM_ROWS* sizeof(float*));
    for(i = 0; i < NUM_ROWS; i++){
    	data[i] = (float*)malloc(NUM_COLS*sizeof(float));
    }
    for(i = 0; i < NUM_ROWS; i++){
    	for(j = 0; j < NUM_COLS; j++){
    		fscanf(db, "%f,", &data[i][j]);
    		if(j < 48)
    		    data[i][j] /= 255.0;
    		printf("%f ", data[i][j]);
    	}
    	printf("\n");
    
    }
    float **test = (float**)malloc(48* sizeof(float*));
    for(i = 0; i < NUM_ROWS; i++){
    	test[i] = (float*)malloc(NUM_COLS*sizeof(float));
    }
    for(i = 0; i < 48; i++){
    	for(j = 0; j < NUM_COLS; j++){
    		fscanf(dbt, "%f,", &test[i][j]);
    		if(j < 48)
    		    test[i][j] /= 255.0;
    		printf("%f ", test[i][j]);
    	}
    	printf("\n");
    
    }
    train_perceptron(&p, data, epochs, learn_rate);
    int r = 0, cont = 0;
    for(i = 0; i < 48; i++){
        r = recognize(p, test[i], 48);
        printf("Result: %d, expected: %.0f\n", r, test[i][51]);
        cont = r == test[i][51]? cont + 1 : cont;
    }
    printf("accuracy = %f\n", (float)cont/(float)48);
    // for(i = 0; i < NUM_ROWS; i++)
    //     free(data[i]);
    // free(data);
    // for(i = 0; i < 48; i++)
    //     free(test[i]);
    // free(test);
    // fclose(db);
    // fclose(dbt);
	return 0;
}

int step_function(float x){
	return x > 0? 1: 0;
}

int recognize(Perceptron p, float *data, int batch_size){
	int i, result = 0;
	for (i = 0; i < batch_size; i++){
		result += p.weights[i] * data[i];
	}
	result -= p.bias;
	return step_function(result);
}

void train_perceptron(Perceptron *p, float **data, int num_epochs, float learn_rate){
	int i, j, k, result = 0;
	for(i = 0; i < p->inputs_qtd; i++){
		(*p).weights[i] = 0; //generates a weight between 0 and 1
	}
	(*p).bias = 0;
	for(i = 0; i < num_epochs; i++){
		for(j = 0; j < NUM_ROWS; j++){
			result = recognize(*p, data[j], p->inputs_qtd);
			if(result != data[j][51]){
			    (*p).bias  += learn_rate*(data[j][51] - result)*data[j][0];
				for(k = 0; k < p->inputs_qtd; k++){
					(*p).weights[k] += learn_rate*(data[j][51] - result)*data[j][k];
				}

			}
		}
	}
	for(i = 0; i < p->inputs_qtd; i++)
	    printf("w[%d] = %f\n", i, p->weights[i]);

}
