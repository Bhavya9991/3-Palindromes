#include<simplecpp>
#include<iomanip>

int calculate_modulus(int value, int base);

class Algorithm;

class Palin_info {

public:

    int flag;

    vector<int> length;

    vector<int> LSD;

    Palin_info(){

        flag = 0;
        length.resize(3);
        LSD.resize(3);

    }

    void set_info(int f, const vector<int> &len, const vector<int> &lsd ){

        set_flag(f);

        set_length(len);

        set_LSD(lsd);

    }

    void Copy_info(const Palin_info &P) {

        set_flag(P.flag);

        set_length(P.length);

        set_LSD(P.LSD);

    }

    void display() {

        cout<<"\nClass Palin_info\n\n";

        if(flag > 6) {

            cout<<"\tFor Class B." << flag - 6 << "\n";

        }

        else {

            cout<<"\tFor Class A." << flag << "\n";

        }

        for(int i=0; i<3; i++){

            cout<< "\tPalindrome:" << i+1 << endl;

            cout << "\t\tLength= " << length[i] << endl;

            cout<<"\t\tLSD=MSD= " << LSD[i] << endl;

        }

    }

    private:

        void set_flag(int i) {

            flag = i;

        }

        void set_length(const vector<int> &v) {

            for(int i=0; i<3; i++){

                length[i] = v[i];
            }
        }

        void set_LSD(const vector<int> &v) {

            for(int i=0; i<3; i++){

                LSD[i] = v[i];
            }
        }

};


class Function {

public:

    int input_var;

    virtual void set_var (const vector<int> &V) = 0;

    virtual int execute () = 0;

    virtual int output(int x) {

        return x;

    }

};


class Range : virtual public Function {

public:

    int index ;
    int ul ;
    int ll ;

    Range(){

        index = ul = ll = 0;

    }

    Range (int index, int ll, int ul){

        this->index = index;
        this->ul = ul;
        this->ll = ll;

    }

    void set_var ( const vector<int> &V ) {

        input_var = V[index];
    }

    int execute () {

        if(input_var >= ll && input_var <= ul)

            return output(1);

        else

            return output(-1);

    }

    void display(){

        cout << "Input=" << input_var << " UL=" << ul << " LL=" << ll << endl;

    }

};

class Modulus : virtual public Function {

public:

    int target;
    int base;
    int constant;
    vector<int> positives;
    vector<int> negatives;

    Modulus() {

        constant = 0;
        target = 0;
        base = 10;
    }

    Modulus (int constant, int target, int base, const vector<int> &v1,const vector<int> &v2) {

        this->constant = constant;

        this->target = target;

        this->base = base;

        positives = v1;

        negatives = v2;

    }

    void set_var (const vector<int> &V) {

        int a,b;

        a = b = 0;

        for(int i = 0; i < positives.size(); i++) {

            a += V[positives[i]];

        }

        for(int i = 0; i < negatives.size(); i++) {

            b += V[negatives[i]];

        }

        input_var = a - b + constant;

    }

    int execute () {

        int x = (input_var + 2*base) % base;
        int z = x;

        if(x!= 0){

            x = 1;

        }

        if(target-x == 0) {

            return output(z);

        }
        else {

            return output(-1);

        }

    }

    void display() {

    cout << "Target=" <<target <<" ";
    cout << "Input=" << input_var << endl;

    }


};



class Condition{

public:

    vector<Function *> C;

    Palin_info result;

    Condition(const vector<Function *> X) {

        C = X;

    }

    void set_result(const Palin_info &P) {

        result.Copy_info(P);
    }

    void set_result(int f, const vector<int> &len, const vector<int> &lsd) {

        result.set_info( f, len, lsd);

    }

    Palin_info & get_info() {

        return result;

    }

};


class Number {

public:

    vector<int> v;

    Palin_info Myinfo;

    int base;

    Number(){

        base = 10;

    }

    void set_number() {

        cout << "Enter the number:\n";

        string s;

        cin >> s;

        int len_of_s = s.length();

        for(int i = len_of_s - 1; i >= 0 ; i-- ){

            v.push_back(s[i] - 48);
        }
    }

    void set_number(const vector<int> indices) {

        v.resize(indices[0]+1);

        for(int i=0; i < indices.size(); i++){

            v[indices[i]] = 1;
        }

    }

    int get_digit(int index) const {

        return v[index];

    }

    int get_length() const{

        return v.size();

    }

    int operator >= (const Number& arg){

        int len1 = get_length();

        int len2 = arg.get_length();

        if(len1 > len2) {


            return 1;

        }

        else {

            if(len1 < len2) {

                return 0;

            }

            else{

                for(int i = len1 - 1; i>=0; i--){

                    if(get_digit(i) == arg.get_digit(i)){

                        continue;

                    }

                    else {

                        if(get_digit(i) > arg.get_digit(i)){

                            return 1;

                        }

                        else {

                            return 0;

                        }

                    }

                }
                return 1;
            }
        }
    }

    Number operator + (const Number& arg){

        int len1 = get_length();

        int len2 = arg.get_length();

        int carry_fwd = 0;

        Number result;

        int tmp;

        int smaller_len = (len1 > len2)? len2 : len1;

        int larger_len = (len1 > len2)? len1 : len2;

        int temp_flag = (len1 > len2)? 1 : 0;

        for(int i = 0; i < smaller_len; i++){

            tmp = get_digit(i) + arg.get_digit(i) + carry_fwd;

            result.v.push_back(calculate_modulus(tmp,base));

            carry_fwd = tmp / base;

        }

        for(int i = smaller_len; i < larger_len; i++){

            if(temp_flag)
                tmp = get_digit(i) + carry_fwd;

            else
                tmp = arg.get_digit(i) + carry_fwd;

            result.v.push_back(calculate_modulus(tmp,base));

            carry_fwd = tmp / base;

        }

        if(carry_fwd > 0){

            result.v.push_back(carry_fwd);

        }

        return result;

    }

    Number operator - (const Number& arg) const{

        Number temp;

        temp.v = v;

        if(temp >= arg){

            Number result;

            int carry_fwd = 0;

            int smaller_len = arg.get_length();

            int larger_len = get_length();

            for(int i = 0; i < smaller_len; i++){

                int val = get_digit(i) - arg.get_digit(i) - carry_fwd;

                if(val >= 0){

                    result.v.push_back(val);

                    carry_fwd = 0;

                }

                else{

                    result.v.push_back( 1*base + val);

                    carry_fwd = 1;
                }
            }

            for(int i = smaller_len; i < larger_len; i++){

                int val = get_digit(i) - carry_fwd;

                if(val >= 0){

                    carry_fwd = 0;

                }

                else{

                    val = 1*base + val;

                    carry_fwd = 1;

                }

                if(i == larger_len - 1 && val == 0){

                        //do nothing.
                }

                else{

                    result.v.push_back(val);

                }

            }

            return result;

        }

        else {

            return arg - temp;

        }

    }

    int Belongs_to(const Condition * C1){

        Function *f;

        int is_C1 ;

        Myinfo.Copy_info(C1->result);

        int n = C1->C.size();

        for(int i = 0; i < n; i++) {

            f = C1->C[i];

            f->set_var(v);

            is_C1 = f->execute();

            if(is_C1 == -1) {

               break;

            }

        }

        if(Myinfo.LSD[2] == -1) {

                    Myinfo.LSD[2] = is_C1;

        }

        return is_C1;
    }

    int Is_special() {

        if((Myinfo.length[0] % 2) == 0) {

            int m = Myinfo.length[0] / 2;

            if(v[m] == 0 || v[m-1] == 0) {

                return 1;

            }

            else return 0;
        }

        else return 0;

    }

    void display () {

        int n = get_length();

        for (int i =n-1; i>=0; i--) {

            cout<<get_digit(i);
        }
        cout << endl;

    }

};

class Matrix {

    public:

    int rows, columns;
    vector<vector<int>> table;

    Matrix(){

        rows = columns = 0;

    }

    void set_table( const vector<vector<int>> arg_table) {

        table = arg_table;
        rows = table.size();
        columns = table[0].size();
    }

    int get_rows() {

        return rows;

    }

    int get_columns() {

        return columns;

    }

    void display(){

        for(int i=0; i<rows; i++){

            for(int j=0; j<columns; j++){

                cout << table[i][j] << " ";

            }

        cout << endl;

        }

    }

};

class AdjustmentTable{

    public:

    int key;
    Matrix data;

    AdjustmentTable(){

    }

    AdjustmentTable(int key, const vector<vector<int>> arg_table){

        this->key = key;
        data.set_table(arg_table);

    }

    Matrix& get_data(){

        return data;

    }

    int match_key(int arg_key){

        if(arg_key==key){

            return 1;

        }

        else {

            return 0;

        }

    }

};

Matrix& Find_Matrix(int key, const vector<AdjustmentTable*> arr){

    int index;

    for(int i = 0; i<arr.size(); i++) {

        if(arr[i]->match_key(key)) {

            index = i;

            break;

        }

    }

    return arr[index]->get_data();

}


class Adjustment {

    public:

    int leftend, rightend, key;

    Matrix data;

    Adjustment() {}

    Adjustment(int k, int l, int r) {

        leftend = l;

        rightend = r;

        key = k;

    }

    int Do_calculation(int column_entry, int table_entry, int base) {

            if (abs(table_entry) < base) {

                return calculate_modulus(column_entry + table_entry, base);

            }

            else {

                if(table_entry > 0) {

                    return calculate_modulus(table_entry - base, base);

                }

                else {

                    return calculate_modulus(base + (table_entry + base), base);

                }

            }

    }

    void Process(Algorithm* X);

};

class Algorithm{

    public:

    int *x, *y, *z;
    int len[3];
    Number input;
    int base;
    int flag;

    Algorithm(){

        flag = 0;

    }


    void compute(const Number& num, int g){

            input = num;

            base = g;

            signature();

            init_var();

            initialize();

            iterate() ;

            terminate() ;

    }

    void set_column (const vector<int> & v, int index) {

        x[index] = v[0];
        y[index] = v[1];
        z[index] = v[2];

    }

    vector<int> get_column(int index){

        vector<int> v;

        v.push_back(x[index]);
        v.push_back(y[index]);
        v.push_back(z[index]);

        return v;
    }

    void init_var(){

        init_x();

        init_y();

        init_z();

    }

    virtual void init_x() {

        len[0] = input.Myinfo.length[0];
        x = new int[len[0]]();
        x[0] = input.Myinfo.LSD[0];

    }

    virtual void init_y(){

        len[1] = input.Myinfo.length[1];
        y = new int[len[1]]();
        y[0] = input.Myinfo.LSD[1];
    }

    virtual void init_z(){

        len[2] = input.Myinfo.length[2];
        z = new int[len[2]]();
        z[0] = input.Myinfo.LSD[2];

    }

    int carry(int index){

        if(index > 0){

            return (x[index] + y[index] + z[index] + carry(index-1) - input.get_digit(index))/base;

        }

        else{

            return (x[index] + y[index] + z[index] - input.get_digit(index))/base;

        }

    }

    void display() {

        int * p[] = {x,y,z};

        for(int i =0; i<3; i++){

            cout << "Palindrome p" << i << " =\t";

            for(int j = 0; j < len[i]; j++){

                cout <<p[i][j];

            }

            cout << endl;

        }

    }

    virtual void signature() = 0;

    virtual void initialize() = 0;

    virtual void iterate() = 0;

    virtual void terminate() = 0;

    virtual Adjustment* Build_Adjustment_instance() = 0;

};

class Algorithm_1 : virtual public Algorithm {

    public:

    void signature(){

        cout << "Inside Algo 1\n\n";
    }

    void initialize() {

        int tmp;

        tmp = input.get_length() - 1;

        tmp = tmp - 2;

        if(tmp%2) {--tmp;}

        if(z[0] <= input.get_digit(tmp) - 1) {

            x[1] = calculate_modulus(input.get_digit(tmp+1) - y[0], base);

        }

        else{

            x[1] = calculate_modulus(input.get_digit(tmp+1) - y[0] - 1, base);

        }

        y[1] = calculate_modulus(input.get_digit(tmp) - z[0] - 1, base);

        z[1] = calculate_modulus(input.get_digit(1) - x[1] - y[1] - carry(0), base);

    }

    void iterate() {

        int tmp = input.get_length() - 1;

        tmp /= 2;

        for(int i = 2; i<tmp; i++){

            if(z[i-1] <= input.get_digit(2*tmp - i -1) - 1){

                x[i] = 1;

            }

            else {

                x[i] = 0;

            }

            y[i] = calculate_modulus(input.get_digit(2*tmp - i - 1) - z[i-1] - 1, base);

            z[i] = calculate_modulus(input.get_digit(i) - x[i] - y[i] - carry(i-1), base);

        }

    }

    void terminate() {

        int tmp = input.get_length() - 1;

        tmp /= 2;

        x[tmp] = 0;


        for(int i=0; i<tmp; i++) {

            x[len[0] - i - 1] = x[i];

            y[len[1] - i - 1] = y[i];

            z[len[2] - i - 1] = z[i];

        }

        flag = 1;
    }

    Adjustment* Build_Adjustment_instance() {

        int m = input.get_length() - 1;

        m /= 2;

        if(flag == 1){

            if(carry(m-1) == 0){

                return new Adjustment(1,m,m-1);

            }

            if(carry(m-1) == 2){

                return new Adjustment(2,m,m-1);

            }

        }

        return new Adjustment(0,m,m);

    }

};

class Algorithm_2 : virtual public Algorithm {

    public:

    void signature(){

        cout << "Inside Algo 2\n\n";
    }

    void initialize() {

        int tmp = input.get_length()-1;

        if(tmp%2 == 0){

            tmp -= 3;

        }
        else{

            tmp -= 2;

        }

        if(z[0] <= input.get_digit(tmp) - 1) {

            x[1] = calculate_modulus(input.get_digit(tmp+1) - y[0], base);

        }

        else {

            x[1] = calculate_modulus(input.get_digit(tmp+1) - y[0] - 1, base);

        }

        y[1] = calculate_modulus(input.get_digit(tmp) - z[0] - 1, base);

        z[1] = calculate_modulus(input.get_digit(1) - x[1] - y[1] -carry(0), base);

    }

    void iterate() {

        int tmp = input.get_length();

        tmp /= 2;

        for(int i=2; i<tmp-1; i++) {

            if (z[i-1] <= input.get_digit(2*tmp - i - 2) - 1) {

                x[i] = 1;

            }

            else {

                x[i] = 0;

            }

            y[i] = calculate_modulus(input.get_digit(2*tmp - i - 2) - z[i-1] - 1, base);

            z[i] = calculate_modulus(input.get_digit(i) - x[i] - y[i] - carry(i-1), base);

        }

    }

    void terminate() {

        int tmp = input.get_length();

        tmp /= 2;

        --tmp;

        x[tmp] = x[len[0] - tmp - 1] = 0;

        y[tmp] = calculate_modulus(input.get_digit(tmp) - z[tmp-1] - carry(tmp-1), base);

        for(int i=0; i<tmp; i++) {

            x[len[0] - i - 1] = x[i];

            y[len[1] - i - 1] = y[i];

            z[len[2] - i - 1] = z[i];

        }

        flag = 1;

    }

    Adjustment* Build_Adjustment_instance() {

        int m = input.get_length();

        m /= 2;

        if(flag == 1) {

            if(carry(m-1) == 0) {

                if(y[m-1] != 0) {

                    return new Adjustment(3,m,m-1);

                }

                if(y[m-1] == 0){

                    if(y[m-2] != 0) {

                        return new Adjustment(4,m,m-2);

                    }

                    if(y[m-2] == 0 && z[m-2] != 0) {

                        return new Adjustment(5,m,m-2);

                    }

                    if(y[m-2] == 0 && z[m-2] == 0) {

                        return new Adjustment(6,m+1,m);

                    }

                }

            }

            if(carry(m-1) == 2) {

                return new Adjustment(7,m,m-2);

            }

        }

        return new Adjustment(0,m,m);

    }

};

class Algorithm_3 : virtual public Algorithm{

    public:

    void signature(){

        cout << "Inside Algo 3\n\n";
    }

    void init_x() {

        len[0] = input.Myinfo.length[0];

        x = new int[len[0]]();

        x[0] = x[len[0] - 1] =  1;

        x[1] = input.Myinfo.LSD[0];

    }

    void initialize() {

        int m = input.get_length() - 1;

        m-= 3;

        if(z[0] <= input.get_digit(m) - 1){

            x[2] = calculate_modulus(input.get_digit(m+1) - y[0], base);

        }

        else{

            x[2] = calculate_modulus(input.get_digit(m+1) - y[0] - 1, base);

        }

        y[1] = calculate_modulus(input.get_digit(m) - z[0] - 1, base);

        z[1] = calculate_modulus(input.get_digit(1) - x[1] - y[1] - carry(0), base);

    }

    void iterate(){

        int m = input.get_length() - 1;

        m /= 2;

        for(int i = 2; i < m-1; i++){

            if(z[i-1] <= input.get_digit(2*(m) - i - 2) - 1){

                x[i+1] = 1;

            }

            else{

                x[i+1] = 0;

            }

            y[i] = calculate_modulus(input.get_digit(2*m - i - 2) - z[i-1] - 1, base);

            z[i] = calculate_modulus(input.get_digit(i) - x[i] - y[i] - carry(i-1), base);

        }

    }

    void terminate() {

        int m = input.get_length() - 1;

        m /= 2;

        m--;

        x[m+1] = 0;

        y[m] = calculate_modulus(input.get_digit(m) - z[m-1] - x[m] - carry(m-1), base);

        for(int i=0; i<m; i++){

            x[len[0] - i - 2] = x[i + 1];

            y[len[1] - i - 1] = y[i];

            z[len[2] - i - 1] = z[i];

        }

        flag = 1;

    }

    Adjustment* Build_Adjustment_instance(){

        int m = input.get_length() - 1;

        m /= 2;

        if(flag) {

            if(flag) {

                if(carry(m-1) == 0) {

                    return new Adjustment(8,m,m-1);

                }

                if(carry(m-1) == 2) {

                    if(y[m-2]!= 0 && z[m-2] != base-1) {

                        return new Adjustment(9,m,m-2);

                    }

                    if(y[m-2]!= 0 && z[m-2] == base-1) {

                        return new Adjustment(10,m,m-2);

                    }

                    if(y[m-2]== 0 && z[m-2] != base-1) {

                        return new Adjustment(11,m+1,m-2);

                    }

                    if(y[m-2]== 0 && z[m-2] == base-1) {

                        return new Adjustment(12,m+1,m-2);

                    }

                }

            }

        }

        return new Adjustment(0,m,m);

    }

};

class Algorithm_4 : virtual public Algorithm {

    public:

    void signature(){

        cout << "Inside Algo 4\n\n";
    }

    void init_x() {

        len[0] = input.Myinfo.length[0];

        x = new int[len[0]]();

        x[0] = x[len[0] - 1] =  1;

        x[1] = input.Myinfo.LSD[0];

    }

    void initialize() {

        int m = input.get_length();

        m -= 4;

        if(z[0] <= input.get_digit(m) - 1) {

            x[2] = calculate_modulus(input.get_digit(m+1) - y[0], base);

        }

        else{

            x[2] = calculate_modulus(input.get_digit(m+1) - y[0] - 1, base);

        }

        y[1] = calculate_modulus(input.get_digit(m) - z[0] - 1, base);

        z[1] = calculate_modulus(input.get_digit(1) - x[1] - y[1] - carry(0), base);

    }

    void iterate() {

        int m = input.get_length();

        m /= 2;

        for(int i=2; i < m-2; i++){

            if(z[i-1] <= input.get_digit(2*m - i - 3) - 1) {

                x[i+1] = 1;

            }

            else{

                x[i+1] = 0;

            }

            y[i] = calculate_modulus(input.get_digit(2*m-i-3) - z[i-1] - 1, base);

            z[i] = calculate_modulus(input.get_digit(i) - x[i] - y[i] - carry(i-1), base);

        }

    }

    void terminate(){

        int m = input.get_length();

        m /= 2;

        m -= 2;

        if(z[m-1] <= input.get_digit(m+1) - 1) {

            x[m+1] = 1;

        }

        else {

            x[m+1] = 0;

        }

        y[m] = calculate_modulus(input.get_digit(m+1) - z[m-1] - 1, base);

        z[m] = calculate_modulus(input.get_digit(m) - x[m] - y[m] - carry(m-1), base);

        for(int i = 0; i <= m; i++) {

            x[len[0] - i - 2] = x[i + 1];

            y[len[1] - i - 1] = y[i];

            z[len[2] - i - 1] = z[i];

        }

        flag = 1;

    }

    Adjustment* Build_Adjustment_instance(){

        int m = input.get_length();

        m /=2;

        int M = m;

        m--;

        if(flag){

            if(x[m] + carry(m-1) == 0 && y[m-1]!= base-1){

                if(z[m-1] != 0){

                    return new Adjustment(13,M-1,M-2);
                }

                if(z[m-1] == 0 && y[m-2] != 0){

                    if(y[m-1] != 1 && z[m-2] != base-1){

                        return new Adjustment(14,M,M-3);
                    }

                    if(y[m-1] != 1 && z[m-2] == base-1){

                        return new Adjustment(15,M,M-3);
                    }

                    if(y[m-1] == 1){

                        return new Adjustment(16,M,M-3);
                    }
                }

                if(z[m-1] == 0 && y[m-2] == 0){

                    if(z[m-2] != base-1){

                        return new Adjustment(17,M+1,M-3);
                    }

                    if(z[m-2] == base-1 && y[m-1] != 1){

                        return new Adjustment(18,M+1,M-3);
                    }

                    if(z[m-2] == base-1 && y[m-1] == 1){

                        return new Adjustment(19,M+1,M-3);
                    }
                }
            }

            if(x[m] + carry(m-1) == 0 && y[m-1] == base-1){

                return new Adjustment(20,M,M-3);

            }

            if(x[m] + carry(m-1) == 2){

                if(x[m] == 0 && carry(m-1) == 2){

                    if(z[m-1] != base-1){

                            return new Adjustment(21,M-1,M-2);
                    }

                    if(z[m-1] == base-1 && z[m-2] != base-1){

                        if(y[m-2] != 0){

                            return new Adjustment(22,M,M-3);
                        }

                        if(y[m-2] == 0){

                            return new Adjustment(23,M+1,M-3);
                        }
                    }

                    if(z[m-1] == base-1 && z[m-2] == base-1){

                        if(y[m-1] < base-2){

                            if(y[m-2] != base-1){

                                return new Adjustment(24,M+1,M-3);
                            }

                            if(y[m-2] == base-1){

                                return new Adjustment(25,M+1,M-3);
                            }

                        }

                        if(y[m-1] >= base-2){

                            if(y[m-2] >= 1){

                                return new Adjustment(26,M+1,M-3);
                            }

                            if(y[m-2] == 0){

                                return new Adjustment(27,M+1,M-3);
                            }

                        }
                    }
                }

                if(x[m] ==1 && carry(m-1) == 1){

                    if(z[m-1] != base-1 && y[m-1] != 0){

                        return new Adjustment(28,M-1,M-2);
                    }

                    if(z[m-1] != base-1 && y[m-1] == 0){

                        return new Adjustment(29,M,M-2);
                    }

                    if(z[m-1] == base-1 && z[m-2] != 0){

                        if(y[m-2] != base-1){

                            return new Adjustment(30,M,M-3);
                        }

                        if(y[m-2] == base-1 && y[m-1] > 1){

                            return new Adjustment(31,M,M-3);
                        }

                        if(y[m-2] == base-1 && y[m-1] == 0){

                            return new Adjustment(32,M,M-3);
                        }

                        if(y[m-2] == base-1 && y[m-1] == 1){

                            return new Adjustment(33,M,M-3);
                        }
                    }

                    if(z[m-1] == base-1 && z[m-2] == 0 && y[m-2] != 0){

                        if(y[m-1] > 1){

                            return new Adjustment(34,M,M-3);
                        }

                        if(y[m-1] == 0){

                            return new Adjustment(35,M,M-3);
                        }

                        if(y[m-1] == 1){

                            return new Adjustment(36,M,M-3);
                        }
                    }

                     if(z[m-1] == base-1 && z[m-2] == 0 && y[m-2] == 0){

                        if(y[m-1] > 1){

                            return new Adjustment(37,M+1,M-3);
                        }

                        if(y[m-1] == 0){

                            return new Adjustment(38,M+1,M-3);
                        }

                        if(y[m-1] == 1){

                            return new Adjustment(39,M+1,M-3);
                        }
                    }
                }
            }

            if(x[m] + carry(m-1) == 3) {

                return new Adjustment(40,M-1,M-2);

            }
        }

        return new Adjustment(0,m,m);

    }
};

Algorithm* Find_Algorithm(const Number & num) {

    if(num.Myinfo.flag < 7){

        if(num.Myinfo.flag > 4) {

            if(num.get_length() % 2 == 0){

                return new Algorithm_1;

            }

            else{

                return new Algorithm_2;

            }

        }

        else{

            if(num.get_length() % 2 == 0){

                return new Algorithm_2;

            }

            else {

                return new Algorithm_1;
            }

        }

    }

    else{

        if(num.get_length() % 2 == 0){

            return new Algorithm_4;

        }

        else {

        return new Algorithm_3;

        }

    }


}

void set_Ranges (vector <Range*> &R, int l, int g){

    Range* tmp;

    tmp = new Range(l-2, 3, g-1);
    R.push_back( tmp );

    tmp = new Range(l-2, 0, 2);
    R.push_back( tmp );

    tmp = new Range(l-1, 2, g-1);
    R.push_back( tmp );

    tmp = new Range(l-1, 1, 1);
    R.push_back( tmp );

    tmp = new Range(l-2, 0, 0);
    R.push_back( tmp );

    tmp = new Range(l-3, 0, 3);
    R.push_back( tmp );

    tmp = new Range(l-3, 0, 2);
    R.push_back( tmp );

    tmp = new Range(l-3, 4, g-1);
    R.push_back( tmp );

    tmp = new Range(l-3, 3, g-1);
    R.push_back( tmp );

    tmp = new Range(l-2, 1, 2);
    R.push_back( tmp );

    tmp = new Range(l-3, 0, 1);
    R.push_back( tmp );

    tmp = new Range(0, 0, 0);
    R.push_back( tmp );

    tmp = new Range(l-3, 2, 3);
    R.push_back( tmp );

    tmp = new Range(0, 1, g-1); // IMPORTANT: this object is no longer needed
    R.push_back( tmp );         // Do not delete this directly, it will affect the order of the sequence.

    tmp = new Range(l-3, 3, 3);
    R.push_back( tmp );

    tmp = new Range(0, 3, 3);
    R.push_back( tmp );

}

void set_Mod (vector <Modulus*> &M, int len, int g){

    Modulus* tmp;

    tmp = new Modulus(1, 1, g, {0}, {len-1, len-2});
    M.push_back(tmp);

    tmp = new Modulus(1, 0, g, {0}, {len-1, len-2});
    M.push_back(tmp);

    tmp = new Modulus(2, 1, g, {0}, {len-1});
    M.push_back(tmp);

    tmp = new Modulus(2, 0, g, {0}, {len-1});
    M.push_back(tmp);

    tmp = new Modulus(0, 1, g, {0}, {len-3});
    M.push_back(tmp);

    tmp = new Modulus(0, 0, g, {0}, {len-3});
    M.push_back(tmp);

    tmp = new Modulus(-3, 1, g, {0}, {});
    M.push_back(tmp);

    tmp = new Modulus(0, 1, g, {0}, {});
    M.push_back(tmp);

}

void set_Conditions (vector<Condition*> &C, vector<Range*> &R, vector<Modulus*> &M,
                     int len, const vector<int> & V, int g) {

    Condition * tmp;

    tmp = new Condition({R[0], M[0]}) ;

    vector <int> arg1 = {len, len-1, len-2};
    vector <int> arg2 = {V[len-1], V[len-2] - 1, -1};

    tmp->set_result(1, arg1, arg2);
    C.push_back(tmp);

    tmp = new Condition({R[0], M[1]}) ;

    arg1 = {len, len-1, len-2};
    arg2 = {V[len-1], V[len-2] - 2, 1};

    tmp->set_result(2, arg1, arg2);
    C.push_back(tmp);

    tmp = new Condition({R[1], R[2], M[2]}) ;
    tmp->set_result(3, {len, len-1, len-2}, {V[len-1]-1, g-1, -1});
    C.push_back(tmp);

    tmp = new Condition({R[1], R[2], M[3]}) ;
    tmp->set_result(4, {len, len-1, len-2}, {V[len-1]-1, g - 2, 1}) ;
    C.push_back(tmp);

    tmp = new Condition({R[3], R[4], R[5], M[4]}) ;
    tmp->set_result(5, {len-1, len-2, len-3}, {g-1, V[len-3] + 1, -1});
    C.push_back(tmp) ;

    tmp = new Condition({R[3], R[4], R[6], M[5]}) ;
    tmp->set_result(6, {len-1, len-2, len-3}, {g-1, V[len-3] + 2, g-1});
    C.push_back(tmp) ;

    tmp = new Condition({R[3], R[1], R[7], M[4]}) ;
    tmp->set_result(7, {len, len-2, len-3}, {V[len-2], V[len-3]-1 , -1});
    C.push_back(tmp);

    tmp = new Condition({R[3], R[1], R[8], M[5]}) ;
    tmp->set_result(8, {len, len-2, len-3}, {V[len-2], V[len-3] - 2, 1});
    C.push_back(tmp);

    tmp = new Condition({R[3], R[9], R[10], R[11]}) ;
    tmp->set_result(9, {len, len-2, len-3}, {V[len-2] - 1, g - 2, 1});
    C.push_back(tmp);

    tmp = new Condition({R[3], R[9], R[11], R[12]}) ;
    tmp->set_result(10, {len, len-2, len-3}, {V[len-2], 1, g-2});
    C.push_back(tmp);

    tmp = new Condition({R[3], R[9], R[6], M[7]}) ;
    tmp->set_result(11, {len, len-2, len-3}, {V[len-2]-1, g-1, -1});
    C.push_back(tmp);

    tmp = new Condition({R[3], R[9], R[14], M[6]}) ;
    tmp->set_result(12, {len, len-2, len-3}, {V[len-2], 2, -1});
    C.push_back(tmp);

    tmp = new Condition({R[3], R[9], R[14], R[15]}) ;
    tmp->set_result(13, {len, len-2, len-3}, {V[len-2], 1, 1});
    C.push_back(tmp);

}

void set_adjustment_tables( vector<AdjustmentTable*> &Table_pool ) {

        AdjustmentTable* T;

        T = new AdjustmentTable (0, { {0},
                                      {0},
                                      {0} } );
        Table_pool.push_back(T);


        T = new AdjustmentTable (1, { {1,0},
                                      {0,0},
                                      {0,0} } );
        Table_pool.push_back(T);


        T = new AdjustmentTable (2, { {1,0},
                                      {-1,-1},
                                      {0,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (3, { {1,1},
                                      {0,-1},
                                      {0,0} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (4, { {1,1,0},
                                      {-1,-12,-1},
                                      {0,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (5, { {0,0,0},
                                      {1,1,1},
                                      {0,-1,-1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (6, { {-1,11,11,-1},
                                      {0,-11,-14,-11},
                                      {10,0,12 ,12} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (7, { {1,1,0},
                                      {-1,-1,-1},
                                      {0,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (8, { {1,0},
                                      {0,0},
                                      {0,0} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (9, { {0,0,0},
                                      {-1,-1,-1},
                                      {0,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (10, { {1,0,0},
                                      {-1,0,-1},
                                      {0,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (11, { {-1,0,-1,0},
                                      {0,-11,-1,-11},
                                      {0,0,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (12, { {-1,1,-1,0},
                                      {0,-11,0,-11},
                                      {0,0,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (13, { {0,0},
                                      {1,1},
                                      {0,-1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (14, { {1,1,0,0},
                                      {-1,-1,-1,-1},
                                      {0,1,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (15, { {2,2,0,0},
                                      {-1,-2,-2,-1},
                                      {0,1,3,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (16, { {1,1,0,0},
                                      {-1,-11,-11,-1},
                                      {0,1,3,0} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (17, { {-1,1,1,-1,0},
                                      {0,-11,-1,-1,-11},
                                      {0,0,1,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (18, { {-1,2,2,-1,0},
                                      {0,-11,-2,-2,-11},
                                      {0,0,1,3,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (19, { {-1,1,1,-1,0},
                                      {0,-11,-11,-11,-11},
                                      {0,0,1,3,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (20, { {1,1,0,0},
                                      {-1,-1,-1,-1},
                                      {0,1,1,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (21, { {0,0},
                                      {-1,-1},
                                      {0,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (22, { {1,1,0,0},
                                      {-1,-2,-2,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (23, { {-1,1,1,-1,0},
                                      {0,-11,-2,-2,-11},
                                      {0,0,1,2,1} } );
        Table_pool.push_back(T);
        T = new AdjustmentTable (24, { {-1,-12,-12,-1,0},
                                      {0,1,2,2,1},
                                      {0,0,-1,-1,-1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (25, { {0,-12,-12,0,0},
                                      {0,1,2,2,1},
                                      {0,0,-1,-1,-1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (26, { {0,2,2,0,0},
                                      {0,-1,-3,-3,-1},
                                      {0,0,1,4,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (27, { {-1,2,2,-1,0},
                                      {0,-11,-3,-3,-11},
                                      {0,0,1,4,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (28, { {0,0},
                                      {-1,-1},
                                      {0,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (29, { {-1,-1,0},
                                      {0,-11,-11},
                                      {0,0,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (30, { {-1,-1,0,0},
                                      {1,1,1,1},
                                      {0,-1,-1,-1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (31, { {1,1,0,0},
                                      {-1,-2,-2,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (32, { {0,0,0,0},
                                      {-1,-12,-12,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (33, { {0,0,0,0,},
                                      {-1,-11,-11,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (34, { {1,1,0,0},
                                      {-1,-2,-2,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (35, { {0,0,0,0},
                                      {-1,-12,-12,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (36, { {0,0,0,0},
                                      {-1,-11,-11,-1},
                                      {0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (37, { {-1,1,1,-1,0},
                                      {0,-11,-2,-2,-11},
                                      {0,0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (38, { {-1,0,0,-1,0},
                                      {0,-11,-12,-12,-11},
                                      {0,0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (39, { {-1,0,0,-1,0},
                                      {0,-11,-11,-11,-11},
                                      {0,0,1,2,1} } );
        Table_pool.push_back(T);

        T = new AdjustmentTable (40, { {0,0},
                                      {-1,-1},
                                      {0,1} } );
        Table_pool.push_back(T);

}

int main(){

    int g = 10;

    Number num;

    num.set_number();

    int len = num.get_length();

    vector<Range*> Range_pool;

    set_Ranges(Range_pool, len, g);

    vector<Modulus*> Mod_pool;

    set_Mod(Mod_pool, len, g);

    vector<Condition*> C_pool;

    set_Conditions(C_pool, Range_pool, Mod_pool, len, num.v, g);

    vector<AdjustmentTable*> Table_pool;

    set_adjustment_tables(Table_pool);

    int check;

    for(int i = 0; i<13; i++) {

        check = num.Belongs_to(C_pool[i]);

        if(check != -1){

            break;
        }

    }

    if(len >= 7) {

        cout << endl;

        if(!(num.Is_special())) {

            Algorithm* X = Find_Algorithm(num);

            X->compute(num,g);

            Adjustment* obj = X->Build_Adjustment_instance();

            obj->data = Find_Matrix(obj->key, Table_pool);

            obj->Process(X);

            X->display();

        }

        else{

            cout << "\nThis is a special number!\n\n";

            int m = num.get_length() / 2;

            Number s;

            s.set_number({m,m-1});

            Number n1 = num - s;

            int k;

            if(n1.get_digit(m)!= 0 && n1.get_digit(m-1)!= 0){

                k = 1;

            }

            else{

                n1 = n1 - s;

                k = 2;

            }

        for(int i = 0; i<13; i++) {

            check = n1.Belongs_to(C_pool[i]);

            if(check != -1){

                break;
            }

        }

            Algorithm* X ;

            if(n1.Myinfo.length[0] % 2) {

                X = new Algorithm_4;

            }

            else{

                X = Find_Algorithm(n1);

            }

            X->compute(n1,g);

            X->display();

            Adjustment* obj = X->Build_Adjustment_instance();

            cout << "key = " << obj->key << endl << endl;

            obj->data = Find_Matrix(obj->key, Table_pool);

            obj->Process(X);

            X->x[m] += k;

            X->x[m-1] += k;

            X->display();


        }

    }

    else{

        cout << "\nNumber too small\n\n";

    }

    return 1;

}

void Adjustment::Process(Algorithm* X) {

    for(int i = leftend; i>=rightend; i--){

        vector<int> v = X->get_column(i);

        for(int j = 0; j < 3; j++){

            v[j] = Do_calculation(v[j], data.table[j][leftend-i], X->base);

        }

        X->set_column(v,i);

    }

}

int calculate_modulus(int val, int base) {

    while(val<0) {

        val += base;

    }
    return (val % base);

}
