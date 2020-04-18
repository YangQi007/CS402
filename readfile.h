#define MAXNAME 64
#define MAXEMPLOYEE 1024

struct person {
    char first_name[MAXNAME], last_name[MAXNAME];
    int id, salary;
}employee;

int open_file(char *filename){
    if(fopen(filename, "r") == NULL)
    return -1;
    return 0;
}

int read_int(int *address){
    if(scanf("%d", address) == 0)
    return -1;
    return 0;
}

int read_float(float *address){
    if(scanf("%f", address) == 0)
    return -1;
    return 0;
}

int read_string(char *address){
    if(scanf("%s", address) == 0)
    return -1;
    return 0;
}

void close_file(FILE *filename){
    fclose(filename);
}

int IDcompare(const void *a, const void *b)
{
        struct person *c = (struct person*) a;
        struct person *d = (struct person*) b;
        return c->id - d->id;
}

int binary_search(const int arr[], int l, int r,int v){
    if (r >= l){
        int mid = l + (r - l)/2;
        if (arr[mid] == v)
            return mid;
        if (arr[mid] > v)
            return binary_search(arr, l, mid-1, v );
        else
            return binary_search(arr, mid+1, r, v);
    }
    return -1;
}


void print_by_key(struct person employee[MAXEMPLOYEE], int key){
     printf("---------------------------------------------------\n");
     printf("First_name     Last_name      SALARY     ID\n");
     printf("%-10s %-10s %10d %10d \n", employee[key].first_name, employee[key].last_name, employee[key].salary, employee[key].id);
     printf("---------------------------------------------------\n");
}

int search_lastname(struct person employee[MAXEMPLOYEE],int n_emp, char last_name[]){
    for (int i=0; i<n_emp; i++){
        if(strcmp(employee[i].last_name, last_name) ==0){
            return i;
        }
    }
    return -1;
}

