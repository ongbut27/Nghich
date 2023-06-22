#include <bits/stdc++.h>

using namespace std;

int RSA_b,RSA_n,RSA_a;
int banMa[1000];
int length;

int GCD(int a, int b)
{
    int r = a%b;
    if (r == 0)
        return b;
    else
        return GCD(b,r);
}

int EuCoLit(int a, int n) // Tính a^-1 mod n
{
    int n0 = n, m;
    int t0 = 0, t1 = 1, q, t;
    if (GCD(a,n) != 1)
        return 0;
    else
    {
        while (n%a != 0)
        {
            q = n/a;
            m = n;
            n = a; a = m%a;
            t = t0 - q*t1;
            t0 = t1; t1 = t;
        }
        if (t < 0)
            t += n0;
        return t;
    }
}

unsigned long long int BinhPhuongVaNhan(int x, int m, int n) // Tính x^m mod n
{
    if (m == 0)
        return 1;
    else if (m == 1)
        return x%n;
    else
    {
        unsigned long long int kq = BinhPhuongVaNhan(x,m/2,n);
        kq = (kq*kq)%n;
        if (m%2 == 0)
            return kq;
        else
            return (x*kq)%n;
    }
}

int GetRandom(int Min, int Max)
{
    srand(time(NULL));
	int computer = rand() % (Max - Min + 1) + Min;
	return computer;
}

// Hàm kiểm tra xem x có phải là số nguyên tố hay không
bool isPrime(long long x, int iter=5) {
    if (x < 2) return false;
    if (x != 2 && x % 2 == 0) return false;
    long long d = x - 1;
    while (d % 2 == 0) {
        d >>= 1;
    }
    for (int i = 0; i < iter; i++) {
        long long a = rand() % (x - 1) + 1;
        long long tmp = d;
        long long mod = BinhPhuongVaNhan(a, tmp, x);
        while (tmp != x - 1 && mod != 1 && mod != x - 1) {
            mod = (mod * mod) % x;
            tmp <<= 1;
        }
        if (mod != x - 1 && tmp % 2 == 0) {
            return false;
        }
    }
    return true;
}

void taoKhoa()
{
    int p=0,q=0;

    while (p == q)
    {
        do
        {
            p = GetRandom(1000,5000);
        } while (isPrime(p) == 0);

        do
        {
            q = GetRandom(1001,5000);
        } while (isPrime(q) == 0);
    }
    //p = 14827; q = 14831;

    //Tạo public key
    RSA_n = p*q;
    int fi = (p-1)*(q-1);

    do
    {
        RSA_b = GetRandom(2,fi);
    } while (GCD(RSA_b,fi) != 1);
    //RSA_b = 4871;

    //Tạo private key
    RSA_a = EuCoLit(RSA_b,fi);

    /*cout << "p = " <<p<<endl;
    cout << "q = " <<q<<endl;
    cout << "b = " <<b<<endl;
    cout << "a = " <<a<<endl;
    cout << "n = " <<n<<endl;*/
}


string MaHoa(string s)
{
    string bm = "";
    int k;
    length = s.size();
    for (int i = 0; i<length; i++)
    {
        k = BinhPhuongVaNhan((s[i]),RSA_b,RSA_n);
        banMa[i] = k/26;
        bm += char(k%26 + 97);
    }
    return bm;
}

string GiaiMa(string s)
{
    int k,tam;
    string br = "";
    for (int i = 0; i<length; i++)
    {
        tam = banMa[i]*26 + int(s[i]-97);
        k = BinhPhuongVaNhan(tam,RSA_a,RSA_n);
        br += char(k);
    }
    return br;
}

int main()
{
    int chon;
    string x,y;

    cout << "=============MA HOA RSA=============\n";
    cout << "Nhap ban ro: "; getline(cin,x);
    taoKhoa();
    cout << "b = "<<RSA_b<<endl;
    cout << "n = "<<RSA_n<<endl;
    cout << "a = "<<RSA_a<<endl;

    cout << "Ban ma la: "<<MaHoa(x)<<endl;
    cout << "1: Giai ma"<<endl;
    cout << "0: Huy bo"<<endl;
    cout << "Ban chon: "; cin>>chon;

    switch (chon){
    case 1:
        cout << "\n=============GIAI MA RSA=============\n";
        cout << "Nhap ban ma: "; cin>>y;
        cout << "Ban ro la: " << GiaiMa(y);
        break;
    }
    return 0;
}
