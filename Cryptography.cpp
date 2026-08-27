#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include <string.h>
#define blockSize 4
#define SIZE 30
#include <vector>
#include <cmath>
#include <climits> // Untuk INT_MAX dan INT_MIN
#include <cctype>  // Untuk isalpha dan isdigit
using namespace std;

string round_keys[16];
string pt;

// Fungsi untuk mengubah vektor ASCII ke string
string ubahAsciiKeString(const vector<int> &nilaiAscii)
{
    string hasil = "";
    for (int nilai : nilaiAscii)
    {
        hasil += static_cast<unsigned char>(nilai); // Gunakan unsigned char
    }
    return hasil;
}

// Fungsi untuk mengubah string menjadi representasi ASCII-nya
vector<int> ubahStringkeAscii(const string& input) {
    vector<int> asciiValues;
    for (char ch : input) {
        asciiValues.push_back(static_cast<int>(ch)); // Mengubah setiap karakter menjadi nilai ASCII
    }
    return asciiValues;
}

// Fungsi Konversi Teks ke Binary
string convertTextToBinary(const string &text)
{
    string binary = "";
    for (char c : text)
    {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

// Fungsi Konversi Binary ke Text
string convertBinaryToText(const string &binary)
{
    string text = "";
    for (size_t i = 0; i < binary.length(); i += 8)
    {
        string byte = binary.substr(i, 8);
        char c = static_cast<char>(bitset<8>(byte).to_ulong());
        text += c;
    }
    return text;
}

int convertBinaryToDecimal(const string& binary)
{
    int decimal = 0;
    int counter = 0;
    int size = binary.length();
    for (int i = size - 1; i >= 0; i--)
    {
        if (binary[i] == '1')
        {
            decimal += pow(2, counter);
        }
        counter++;
    }
    return decimal;
}

string convertDecimalToBinary(int decimal)
{
    string binary;
    while (decimal != 0)
    {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal = decimal / 2;
    }
    while (binary.length() < 4)
    {
        binary = "0" + binary;
    }
    return binary;
}

// Fungsi untuk mengonversi string ke hexadecimal
string stringToHex(const string& input) {
    stringstream hexStream;

    // Loop setiap karakter dalam string input
    for (unsigned char c : input) {
        hexStream << hex << setw(2) << setfill('0') << static_cast<int>(c);
    }

    return hexStream.str();
}

// Fungsi untuk mengonversi hexa ke string
string hexToString(const string& hex) {
    string result;

    // Pastikan panjang string hexa adalah genap
    if (hex.length() % 2 != 0) {
        cout << "Hex string length should be even!" << endl;
        return "";
    }

    // Membaca pasangan dua karakter hexa
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2); // Ambil 2 karakter per iterasi
        unsigned int byte = stoi(byteString, nullptr, 16); // Mengonversi hexa ke desimal
        result += static_cast<char>(byte); // Konversi desimal ke karakter dan tambahkan ke hasil
    }

    return result;
}

// Fungsi cari MAX MIN ASCII
pair<int, int> cariMaxMinASCII(const string &kunci)
{
    int maxASCII = INT_MIN, minASCII = INT_MAX;
    for (char karakter : kunci)
    {
        int nilaiASCII = static_cast<int>(karakter);
        maxASCII = max(maxASCII, nilaiASCII);
        minASCII = min(minASCII, nilaiASCII);
    }
    return {maxASCII, minASCII};
}

// Fungsi untuk mencari bilangan prima ke-n
int cariBilanganPrima(int urutan)
{
    int jumlah = 0, angka = 2;
    while (true)
    {
        bool prima = true;
        for (int i = 2; i <= sqrt(angka); i++)
        {
            if (angka % i == 0)
            {
                prima = false;
                break;
            }
        }
        if (prima)
        {
            jumlah++;
            if (jumlah == urutan)
                return angka;
        }
        angka++;
    }
}

// Fungsi Cari Kelipatan 25
int cariKelipatan25(int urutan)
{
    return 25 * urutan;
}

// Fungsi menghitung deret aritmatika Sn
int deretAritmatika(int urutan, int sukuPertama, int sukuTerakhir)
{
    int hasil = round((urutan / 2.0) * (sukuPertama + sukuTerakhir));
    return hasil;
}

vector<int> enkripsiKunci(const string &plainkey, const string &kunciPembangkits) {
    vector<int> hasilEnkripsi;
    int hurufCounter = 0, angkaCounter = 0, simbolCounter = 0;

    // Cari nilai min dan max ASCII dari plainkey
    auto [maxASCII, minASCII] = cariMaxMinASCII(kunciPembangkits);

    // Iterasi untuk setiap karakter dalam plainkey
    for (int i = 0; i < plainkey.length(); ++i) {
        int asciiPlainkey = static_cast<int>(plainkey[i]); // Nilai ASCII karakter plainkey
        char kunciKarakter = kunciPembangkits[i % kunciPembangkits.length()]; // Karakter kunci pembangkit
        int asciiKunci = static_cast<int>(kunciKarakter); // Nilai ASCII karakter kunci pembangkit

        int pergeseran = 0;
        int urutanKunci;

        // Tentukan urutan berdasarkan jenis karakter pada kunci pembangkit
        if (isalpha(kunciKarakter)) {
            // Jika huruf, gunakan urutan huruf
            urutanKunci = ++hurufCounter;
            int prima = cariBilanganPrima(urutanKunci); // Ambil bilangan prima berdasarkan urutan
            pergeseran = prima;
        } else if (isdigit(kunciKarakter)) {
            // Jika angka, gunakan urutan angka
            urutanKunci = ++angkaCounter;
            int kelipatan25 = cariKelipatan25(urutanKunci); // Ambil kelipatan 25 berdasarkan urutan
            pergeseran = kelipatan25;
        } else {
            // Jika simbol lain, gunakan urutan simbol
            urutanKunci = ++simbolCounter;
            int deret = deretAritmatika(urutanKunci, minASCII, maxASCII); // Deret aritmatika
            pergeseran = deret;
        }

        // Menggeser plainkey berdasarkan pergeseran yang dihitung
        int hasil = (asciiPlainkey + pergeseran) % 256;
        hasilEnkripsi.push_back(hasil);
    }

    return hasilEnkripsi;
}

vector<int> dekripsiKunci(const string &plainkey, const string &kunciPembangkits) {
    vector<int> hasilDekripsi;
    int hurufCounter = 0, angkaCounter = 0, simbolCounter = 0;

    // Cari nilai min dan max ASCII dari plainkey
    auto [maxASCII, minASCII] = cariMaxMinASCII(kunciPembangkits);

    // Iterasi untuk setiap karakter dalam plainkey
    for (int i = 0; i < plainkey.length(); ++i) {
        int asciiEncrypted = static_cast<int>(plainkey[i]); // Nilai ASCII karakter encryptedText
        char kunciKarakter = kunciPembangkits[i % kunciPembangkits.length()]; // Karakter kunci pembangkit
        int asciiKunci = static_cast<int>(kunciKarakter); // Nilai ASCII karakter kunci pembangkit

        int pergeseran = 0;
        int urutanKunci;

        // Tentukan urutan berdasarkan jenis karakter pada kunci pembangkit
        if (isalpha(kunciKarakter)) {
            // Jika huruf, gunakan urutan huruf
            urutanKunci = ++hurufCounter;
            int prima = cariBilanganPrima(urutanKunci); // Ambil bilangan prima berdasarkan urutan
            pergeseran = prima;
        } else if (isdigit(kunciKarakter)) {
            // Jika angka, gunakan urutan angka
            urutanKunci = ++angkaCounter;
            int kelipatan25 = cariKelipatan25(urutanKunci); // Ambil kelipatan 25 berdasarkan urutan
            pergeseran = kelipatan25;
        } else {
            // Jika simbol lain, gunakan urutan simbol
            urutanKunci = ++simbolCounter;
            int deret = deretAritmatika(urutanKunci, minASCII, maxASCII); // Deret aritmatika
            pergeseran = deret;
        }

        // Menggeser encryptedText untuk mendapatkan plainkey
        int hasil = (asciiEncrypted - pergeseran + 256) % 256; // Menambahkan 256 untuk mencegah hasil negatif
        hasilDekripsi.push_back(hasil);
    }

    return hasilDekripsi;
}

// Fungsi untuk enkripsi Vigenere dengan nilai ASCII
vector<int> enkripsiVigenere (const vector<int> &plainTextASCII, const vector<int> &kunciASCII) {
    // Perluas kunci agar panjangnya sama dengan panjang plainteks
    vector<int> kunciDimodifikasi = kunciASCII;
    while (kunciDimodifikasi.size() < plainTextASCII.size()) {
        kunciDimodifikasi.insert(kunciDimodifikasi.end(), kunciDimodifikasi.begin(), kunciDimodifikasi.end());
    }
    kunciDimodifikasi.resize(plainTextASCII.size()); // Sesuaikan panjang kunci dengan plainteks

    vector<int> hasilVigenere;
    for (size_t i = 0; i < plainTextASCII.size(); ++i) {
        int asciiPlainteks = plainTextASCII[i];
        int asciiKunci = kunciDimodifikasi[i];

        // Enkripsi dengan operasi Vigenere (penjumlahan dan mod 256)
        int hasil = (asciiPlainteks + asciiKunci) % 256;

        // Simpan hasil enkripsi
        hasilVigenere.push_back(hasil);
    }
    return hasilVigenere;
}

vector<int> dekripsiVigenere(const vector<int> &cipherTextASCII, const vector<int> &kunciASCII) {
    // Perluas kunci agar panjangnya sama dengan panjang cipherteks
    vector<int> kunciDimodifikasi = kunciASCII;
    while (kunciDimodifikasi.size() < cipherTextASCII.size()) {
        kunciDimodifikasi.insert(kunciDimodifikasi.end(), kunciDimodifikasi.begin(), kunciDimodifikasi.end());
    }
    kunciDimodifikasi.resize(cipherTextASCII.size()); // Sesuaikan panjang kunci dengan cipherteks

    vector<int> hasilDekripsi;
    for (size_t i = 0; i < cipherTextASCII.size(); ++i) {
        int asciiCipherteks = cipherTextASCII[i];
        int asciiKunci = kunciDimodifikasi[i];

        // Dekripsi dengan operasi Vigenere (pengurangan dan mod 256)
        int hasil = (asciiCipherteks - asciiKunci + 256) % 256; // +256 untuk menghindari hasil negatif

        // Simpan hasil dekripsi
        hasilDekripsi.push_back(hasil);
    }
    return hasilDekripsi;
}

string Xor(string a, string b) {
    // Pastikan kedua string memiliki panjang yang sama
    while (a.size() < b.size()) a = "0" + a; // Pad a dengan 0 di kiri
    while (b.size() < a.size()) b = "0" + b; // Pad b dengan 0 di kiri

    string result = "";
    int size = a.size(); // Panjang sekarang sudah sama
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            result += "1";
        } else {
            result += "0";
        }
    }
    return result;
}

// Fungsi adjustBitLength
string adjustBitLength(const string &input)
{
    string adjustedInput = input;

    // If length is less than 64, add 0s to the end
    while (adjustedInput.length() < 64)
    {
        adjustedInput += "0";
    }

    // If length is more than 64, trim to 64
    if (adjustedInput.length() > 64)
    {
        adjustedInput = adjustedInput.substr(0, 64);
    }

    return adjustedInput;
}

string shift_left_once(string key_chunk)
{
    string shifted = "";
    for (int i = 1; i < 28; i++)
    {
        shifted += key_chunk[i];
    }
    shifted += key_chunk[0];
    return shifted;
}

string shift_left_twice(string key_chunk)
{
    string shifted = "";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j < 28; j++)
        {
            shifted += key_chunk[j];
        }
        shifted += key_chunk[0];
        key_chunk = shifted;
        shifted = "";
    }
    return key_chunk;
}

// generate key
void generate_keys(string key)
{
    // The PC1 table
    int pc1[56] =
        {
            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4};
    // The PC2 table
    int pc2[48] =
        {
            14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32};
    // 1. Compressing the key using the PC1 table
    string perm_key = "";
    for (int i = 0; i < 56; i++)
    {
        perm_key += key[pc1[i] - 1];
    }
    // 2. Dividing the key into two equal halves
    string left = perm_key.substr(0, 28);
    string right = perm_key.substr(28, 28);
    for (int i = 0; i < 16; i++)
    {
        // 3.1. For rounds 1, 2, 9, 16 the key_chunks
        // are shifted by one.
        if (i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = shift_left_once(left);
            right = shift_left_once(right);
        }
        // 3.2. For other rounds, the key_chunks
        // are shifted by two
        else
        {
            left = shift_left_twice(left);
            right = shift_left_twice(right);
        }
        // Combining the two chunks
        string combined_key = left + right;
        string round_key = "";
        // Finally, using the PC2 table to transpose the key bits
        for (int i = 0; i < 48; i++)
        {
            round_key += combined_key[pc2[i] - 1];
        }
        round_keys[i] = round_key;
    }
}

string DES()
{
   // The initial permutation table
	int initial_permutation[64] =
	{
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
	};
	// The expansion table
	int expansion_table[48] =
	{
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
	};
	// The substitution boxes. The should contain values
	// from 0 to 15 in any order.
	int substition_boxes[8][4][16]=
	{
	    {
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
        },
        {
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
        },
        {
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
        },
        {
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
        },
        {
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
        },
        {
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
        },
        {
            4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
        },
        {
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
        }
    };
	// The permutation table
	int permutation_tab[32] =
	{
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
	};
	// The inverse permutation table
	int inverse_permutation[64]=
	{
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
	};
	//1. Applying the initial permutation
  	string perm = "";
	for(int i = 0; i < 64; i++)
    {
		perm += pt[initial_permutation[i]-1];
	}
	// 2. Dividing the result into two equal halves
	string left = perm.substr(0, 32);
	string right = perm.substr(32, 32);
	// The plain text is encrypted 16 times
	for(int i=0; i<16; i++)
	{
    	string right_expanded = "";
		// 3.1. The right half of the plain text is expanded
    	for(int i = 0; i < 48; i++)
    	{
      		right_expanded += right[expansion_table[i]-1];
        };  // 3.3. The result is xored with a key
		string xored = Xor(round_keys[i], right_expanded);
		string res = "";
		// 3.4. The result is divided into 8 equal parts and passed
		// through 8 substitution boxes. After passing through a
		// substituion box, each box is reduces from 6 to 4 bits.
		for(int i=0;i<8; i++)
		{
			// Finding row and column indices to lookup the
			// substituition box
      		string row1= xored.substr(i*6,1) + xored.substr(i*6 + 5,1);
      		int row = convertBinaryToDecimal(row1);
      		string col1 = xored.substr(i*6 + 1,1) + xored.substr(i*6 + 2,1) + xored.substr(i*6 + 3,1) + xored.substr(i*6 + 4,1);;
			int col = convertBinaryToDecimal(col1);
			int val = substition_boxes[i][row][col];
			res += convertDecimalToBinary(val);
		}
		// 3.5. Another permutation is applied
		string perm2 ="";
		for(int i = 0; i < 32; i++)
		{
			perm2 += res[permutation_tab[i]-1];
		}
		// 3.6. The result is xored with the left half
		xored = Xor(perm2, left);
		// 3.7. The left and the right parts of the plain text are swapped
		left = xored;
		if(i < 15)
		{
			string temp = right;
			right = xored;
			left = temp;
		}
	}
	// 4. The halves of the plain text are applied
	string combined_text = left + right;
	string ciphertext ="";
	// The inverse of the initial permuttaion is applied
	for(int i = 0; i < 64; i++)
	{
		ciphertext+= combined_text[inverse_permutation[i]-1];
	}
	//And we finally get the cipher text
	return ciphertext;
}

// Fungsi untuk menghitung faktorial
int faktorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * faktorial(n - 1);
}

vector<int> enkripsiPesan(const string &pesan, const string &kunci) {
    vector<int> hasilEnkripsiPesan;
    int urutanGenap = 1;  // Urutan untuk faktorial
    int urutanGanjil = 1; // Urutan untuk kelipatan 7

    for (int i = 0; i < pesan.length(); ++i) {
        int asciiPesan = pesan[i];
        int asciiKunci = kunci[i % kunci.length()];

        // Tentukan apakah kunci genap atau ganjil
        bool isGenap = (asciiKunci % 2 == 0);

        if (isGenap) {
            // Geser ke kanan sebanyak faktorial
            int hasil = asciiPesan + faktorial(urutanGenap);
            hasil = (hasil % 256 + 256) % 256; // Pastikan hasil selalu positif
            hasilEnkripsiPesan.push_back(hasil);
            urutanGenap++;
        } else {
            // Geser ke kiri sebanyak kelipatan 7
            int hasil = asciiPesan - (7 * urutanGanjil);
            hasil = (hasil % 256 + 256) % 256; // Pastikan hasil selalu positif
            hasilEnkripsiPesan.push_back(hasil);
            urutanGanjil++;
        }
    }

    return hasilEnkripsiPesan;
}

vector<int> dekripsiPesan(const string &pesanEnkripsi, const string &kunci) {
    vector<int> hasilDekripsiPesan;
    int urutanGenap = 1;  // Urutan untuk faktorial
    int urutanGanjil = 1; // Urutan untuk kelipatan 7

    for (int i = 0; i < pesanEnkripsi.size(); ++i) {
        int asciiEnkripsi = pesanEnkripsi[i];
        int asciiKunci = kunci[i % kunci.length()];

        // Tentukan apakah kunci genap atau ganjil
        bool isGenap = (asciiKunci % 2 == 0);

        if (isGenap) {
            // Geser ke kiri sebanyak faktorial
            int hasil = asciiEnkripsi - faktorial(urutanGenap);
            hasil = (hasil % 256 + 256) % 256; // Pastikan hasil selalu positif
            hasilDekripsiPesan.push_back(hasil);
            urutanGenap++;
        } else {
            // Geser ke kanan sebanyak kelipatan 7
            int hasil = asciiEnkripsi + (7 * urutanGanjil);
            hasil = (hasil % 256 + 256) % 256; // Pastikan hasil selalu positif
            hasilDekripsiPesan.push_back(hasil);
            urutanGanjil++;
        }
    }

    return hasilDekripsiPesan;
}

// Tabel karakter Base64
const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

// Fungsi konversi heksadesimal ke biner
string hexToBinary(const string &hex) {
    string binary = "";
    for (char c : hex) {
        int decimal = isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
        binary += bitset<4>(decimal).to_string(); // Konversi tiap hexa ke 4-bit biner
    }
    return binary;
}

// Fungsi konversi biner ke desimal (untuk 4-bit potongan Base64)
vector<int> binaryToDecimal(const string &binary, int chunkSize = 4) {
    vector<int> decimals;
    for (size_t i = 0; i < binary.size(); i += chunkSize) {
        string chunk = binary.substr(i, chunkSize);
        if (chunk.size() < chunkSize) {
            chunk += string(chunkSize - chunk.size(), '0'); // Menambahkan padding jika ukuran kurang dari 4-bit
        }
        decimals.push_back(bitset<4>(chunk).to_ulong());
    }
    return decimals;
}

// Fungsi pembagian biner menjadi 6 bit untuk Base64 encoding
vector<string> splitTo6Bit(const string &binary) {
    vector<string> chunks;
    for (size_t i = 0; i < binary.size(); i += 6) {
        chunks.push_back(binary.substr(i, 6));
    }
    // Tambahkan padding '0' jika potongan terakhir kurang dari 6 bit
    if (!chunks.empty() && chunks.back().size() < 6) {
        chunks.back() += string(6 - chunks.back().size(), '0');
    }
    return chunks;
}

// Fungsi konversi desimal ke karakter Base64
string decimalToBase64(const vector<int> &decimals) {
    string base64;
    for (int value : decimals) {
        base64 += base64_chars[value];
    }
    while (base64.size() % 4 != 0) { // Tambahkan padding '=' jika perlu
        base64 += '=';
    }
    return base64;
}

// Fungsi untuk membalik tabel karakter Base64 ke indeksnya
map<char, int> buildReverseBase64Map() {
    map<char, int> reverseMap;
    for (size_t i = 0; i < base64_chars.size(); ++i) {
        reverseMap[base64_chars[i]] = i;
    }
    return reverseMap;
}

// Fungsi konversi Base64 ke biner
string base64ToBinary(const string &base64) {
    map<char, int> reverseMap = buildReverseBase64Map();
    string binary = "";
    for (char c : base64) {
        if (c == '=') break; // Abaikan padding
        int value = reverseMap[c];
        binary += bitset<6>(value).to_string(); // Konversi ke 6-bit biner
    }
    return binary;
}

// Fungsi Encode: Hexadecimal ke Base64
string encodeBase64(const string &hexInput) {
    // Langkah 1: Konversi hex ke biner
    string binary = hexToBinary(hexInput);

    // Langkah 2: Bagi biner menjadi potongan-potongan 6-bit
    vector<string> binaryChunks = splitTo6Bit(binary);

    // Langkah 3: Konversi tiap potongan 6-bit biner ke desimal
    vector<int> decimals;
    for (const string& chunk : binaryChunks) {
        decimals.push_back(bitset<6>(chunk).to_ulong());
    }

    // Langkah 4: Konversi desimal ke karakter Base64
    return decimalToBase64(decimals);
}

// Fungsi Decode: Base64 ke Hexadecimal
string decodeBase64(const string &base64Input) {
    // Langkah 1: Konversi Base64 ke biner
    string binary = base64ToBinary(base64Input);

    // Langkah 2: Hapus padding 0 di sisi paling kanan setelah konversi biner
    size_t last_non_zero = binary.find_last_not_of('0');
    if (last_non_zero != string::npos) {
        binary = binary.substr(0, last_non_zero + 1); // Hapus bit 0 padding di akhir
    }

    // Langkah 3: Konversi biner ke desimal (4-bit per potongan)
    vector<int> decimals = binaryToDecimal(binary, 4);

    // Langkah 4: Konversi desimal ke hexadecimal
    string hexOutput = "";
    for (int decimal : decimals) {
        stringstream ss;
        ss << hex << uppercase << setw(1) << setfill('0') << decimal; // 1 digit hex
        hexOutput += ss.str();
    }

    return hexOutput;
}

// Fungsi utama untuk enkripsi kunci
void encryptKey()
{
    string plainkey, kuncipembangkit;
    cout << "Masukkan plainkey: ";
    cin >> plainkey;
    cout << "Masukkan kunci pembangkit: ";
    cin >> kuncipembangkit;

    // Proses enkripsi kunci pembangkit
    vector<int> modifkey = enkripsiKunci(plainkey, kuncipembangkit);

     cout << "\nHasil Kunci Modifikasi:\n";
    for (int nilai : modifkey)
    {
        cout << nilai << " ";
    }
    cout << "\nString Kunci Modifikasi: " << ubahAsciiKeString(modifkey) << endl;

    // Proses enkripsi plainteks menggunakan Vigenere
    vector <int> kuncipAscii = ubahStringkeAscii(kuncipembangkit);
    vector <int> hasilEVigenere = enkripsiVigenere(modifkey, kuncipAscii);
     // Tampilkan hasil enkripsi dalam bentuk ASCII
    cout << "\nHasil Enkripsi Vigenere:\n";
    cout << "ASCII: ";
    for (int hasil : hasilEVigenere)
    {
        cout << hasil << " ";
    }
    cout << "\n";

    // Tampilkan hasil enkripsi dalam bentuk string
    cout << "String: ";
    for (int hasil : hasilEVigenere)
    {
        cout << static_cast<char>(hasil);  // Konversi ASCII kembali ke karakter
    }
    cout << endl;

    string plainkeystring = ubahAsciiKeString (hasilEVigenere);

    string binaryKey = convertTextToBinary(kuncipembangkit);
    string binaryPlainKey = convertTextToBinary(plainkeystring);

    binaryKey = adjustBitLength(binaryKey);
    binaryPlainKey = adjustBitLength(binaryPlainKey);

    generate_keys(binaryKey);
    pt = binaryPlainKey;
    string cipherText = DES();
    string hasilDes = convertBinaryToText(cipherText);

    cout << "\nHasil Akhir Enkripsi kunci DES:\n";
    cout << "ASCII: ";
    for (char karakter : hasilDes)
    {
        cout << static_cast<int>(static_cast<unsigned char>(karakter)) << " ";
    }
    cout << "\nString: " << hasilDes;
    cout << "\nHexaDecimal: " << stringToHex(hasilDes);
}

void encryptMessage()
{
    string plainteks, kunci;
    cout << "Masukkan plainteks: ";
    cin >> plainteks;
    cout << "Masukkan kunci pembangkit: ";
    cin >> kunci;

    // Enkripsi pesan
    vector<int> hasilEnkripsiPesan = enkripsiPesan(plainteks, kunci);

    cout << "\nHasil Pesan Modifikasi:\n";
    cout << "ASCII: ";
    for (int nilai : hasilEnkripsiPesan)
    {
        cout << nilai << " ";
    }
    string hasilEnkripsiPesanString = ubahAsciiKeString(hasilEnkripsiPesan);
    cout << "\nString Pesan Modifikasi: " << hasilEnkripsiPesanString << endl;

    string binarykunci = convertTextToBinary(kunci);
    string binaryenkrip = convertTextToBinary(hasilEnkripsiPesanString);

    // Lakukan operasi XOR
    string hasilXorBinary = Xor(binaryenkrip, binarykunci);
    string enkripsiXorString = convertBinaryToText (hasilXorBinary);

    cout << "\nHasil Xor:\n";
    cout << "ASCII: ";
    for (char karakter : enkripsiXorString)
    {
        cout << static_cast<int>(static_cast<unsigned char>(karakter)) << " ";
    }
    cout << "\nString: " << enkripsiXorString << endl;

    string binaryPlainM = convertTextToBinary(enkripsiXorString);

    string binaryME = adjustBitLength(binarykunci);
    binaryPlainM = adjustBitLength(binaryPlainM);

    generate_keys(binaryME);
    pt = binaryPlainM;
    string cipherText = DES();
    string hasilDes = convertBinaryToText(cipherText);

    cout << "\nHasil Akhir Enkripsi Pesan DES:\n";
    cout << "ASCII: ";
    for (char karakter : hasilDes)
    {
        cout << static_cast<int>(static_cast<unsigned char>(karakter)) << " ";
    }
    cout << "\nString: " << hasilDes << endl;

    string plainteksHex = stringToHex(hasilDes);
    string kunciHex = stringToHex(kunci);

    string encodechipertext = encodeBase64(plainteksHex);
    cout << "\nChiperText Hasil Base64:\n";
    cout << "String: " << encodechipertext << endl;

    string encodechiperkey = encodeBase64(kunciHex);
    cout << "\nChiperKey Hasil Base64:\n";
    cout << "String: " << encodechiperkey << endl;
}

// Fungsi untuk menghapus padding nol dari teks hasil dekripsi
string removePadding(const string &text) {
    size_t last_non_zero = text.find_last_not_of('\0'); // Cari posisi terakhir karakter bukan nol
    if (last_non_zero != string::npos) {
        return text.substr(0, last_non_zero + 1); // Kembalikan substring tanpa padding
    }
    return ""; // Jika semua karakter adalah nol, kembalikan string kosong
}

void decryptMessage()
{
    string chiperteksD, kunciD;
    cout << "Masukkan ChiperText: ";
    cin >> chiperteksD;
    cout << "Masukkan ChiperKey: ";
    cin >> kunciD;

    string decodechipertext = decodeBase64(chiperteksD);
    string plainteksString = hexToString(decodechipertext);
    cout << "\nChiperText Hasil Base64:\n";
    cout << "String: " << plainteksString << endl;

    string decodechiperkey = decodeBase64(kunciD);
    string kunciString = hexToString(decodechiperkey);
    cout << "\nChiperKey Hasil Base64:\n";
    cout << "String: " << kunciString << endl;

    // Convert key and plain text to binary
    string binaryKeyd = convertTextToBinary(kunciString);
    string binaryPlainTextd = convertTextToBinary(plainteksString);

    // Adjust bit length
    binaryKeyd = adjustBitLength(binaryKeyd);
    binaryPlainTextd = adjustBitLength(binaryPlainTextd);

    generate_keys(binaryKeyd);

    pt = binaryPlainTextd;

    int i = 15;
    int j = 0;
    while (i > j)
    {
        string temp = round_keys[i];
        round_keys[i] = round_keys[j];
        round_keys[j] = temp;
        i--;
        j++;
    }

    string decryptedText = DES();

    // Convert binary to text
    string decryptedTextInText = convertBinaryToText(decryptedText);

    // Hapus padding dari hasil DES
    decryptedTextInText = removePadding(decryptedTextInText);

    cout << "\nHasil Dekripsi Pesan dengan DES:\n";
    cout << "ASCII: ";
    for (char karakter : decryptedTextInText)
    {
        cout << static_cast<int>(static_cast<unsigned char>(karakter)) << " ";
    }
    cout << "\nString: " << decryptedTextInText << endl;

    decryptedTextInText = convertTextToBinary(decryptedTextInText);
    string binaryKey = convertTextToBinary(kunciString);

    // Lakukan operasi XOR
    string DeXorBinary = Xor(decryptedTextInText, binaryKey);
    string dekripsiXorString = convertBinaryToText (DeXorBinary);

    cout << "\nHasil Xor:\n";
    cout << "ASCII: ";
    for (char karakter : dekripsiXorString)
    {
        cout << static_cast<int>(static_cast<unsigned char>(karakter)) << " ";
    }
    cout << "\nString: " << dekripsiXorString << endl;

    // Enkripsi pesan
    vector<int> hasilDekripsiPesan = dekripsiPesan(dekripsiXorString, kunciString);

    cout << "\nHasil Pesan Modifikasi:\n";
    cout << "ASCII: ";
    for (int nilai : hasilDekripsiPesan)
    {
        cout << nilai << " ";
    }
    string hasilDekripsiPesanString = ubahAsciiKeString(hasilDekripsiPesan);
    cout << "\nPesan yang sebenarnya adalah: " << hasilDekripsiPesanString << endl;
}

void decryptKey()
{
    string KunciKD, CiperkeyD;
    cout << "Masukkan ChiperKey: ";
    cin >> CiperkeyD;
    cout << "Masukkan Kunci Pembangkit: ";
    cin >> KunciKD;

    string StringCK = hexToString(CiperkeyD);

    // Convert key and plain text to binary
    string KDKunci = convertTextToBinary(KunciKD);
    string KDChiperkey = convertTextToBinary(StringCK);

    // Adjust bit length
    KDKunci = adjustBitLength(KDKunci);
    KDChiperkey = adjustBitLength(KDChiperkey);

    generate_keys(KDKunci);

    pt = KDChiperkey;

    int i = 15;
    int j = 0;
    while (i > j)
    {
        string temp = round_keys[i];
        round_keys[i] = round_keys[j];
        round_keys[j] = temp;
        i--;
        j++;
    }

    string decryptedText = DES();

    // Convert binary to text
    string decryptedchiperkeyDES= convertBinaryToText(decryptedText);

    // Hapus padding dari hasil DES
    decryptedchiperkeyDES = removePadding(decryptedchiperkeyDES);

    cout << "\nHasil Dekripsi Kunci dengan DES:\n";
    cout << "ASCII: ";
    for (char karakter : decryptedchiperkeyDES)
    {
        cout << static_cast<int>(static_cast<unsigned char>(karakter)) << " ";
    }
    cout << "\nString: " << decryptedchiperkeyDES << endl;

    // Proses dekripsi plainteks menggunakan Vigenere
    vector <int> kunciDecAscii = ubahStringkeAscii(KunciKD);
    vector <int> DecAscii = ubahStringkeAscii(decryptedchiperkeyDES);
    vector <int> hasilDVigenere = dekripsiVigenere(DecAscii, kunciDecAscii);
     // Tampilkan hasil enkripsi dalam bentuk ASCII
    cout << "\nHasil Dekripsi Kunci dengan Vigenere:\n";
    cout << "ASCII: ";
    for (int hasil : hasilDVigenere)
    {
        cout << hasil << " ";
    }
    string hasilDekripsiPesanString = ubahAsciiKeString(hasilDVigenere);
    cout << "\nString: " << hasilDekripsiPesanString << endl;

    // Proses enkripsi kunci pembangkit
    vector<int> decmodifkey = dekripsiKunci(hasilDekripsiPesanString, KunciKD);

     cout << "\nKunci yang sebenarnya adalah:\n";
    for (int nilai : decmodifkey)
    {
        cout << nilai << " ";
    }
    cout << "\nString: " << ubahAsciiKeString(decmodifkey) << endl;
}

int main()
{
    int jawab;
menu:
    cout << "  ****************************************************************  " << endl;
    cout << "         PROGRAM ALGORITMA VINEGERE, DES, CAESAR, DAN BASE64        " << endl;
    cout << "           OLEH DEVINKA INTAN SAGITA DAN DEWI SRI HARTATI           " << endl;
    cout << "  ****************************************************************  " << endl;
    cout << "\t1.) Enkripsi Kunci\n";
    cout << "\t2.) Enkripsi Pesan\n";
    cout << "\t3.) Deskripsi Pesan\n";
    cout << "\t4.) Deskripsi Kunci\n";
    cout << "\t5.) Selesai\n";
    cout << "\tSilahkan memilih menu sesuai nomor... " << endl;
    cout << "\tPilihan Anda: ";
    cin >> jawab;
    system("cls");
    switch (jawab)
    {
    case 1:
    {
        cout << "  ************************  " << endl;
        cout << "       ENKRIPSI KUNCI       " << endl;
        cout << "  ************************  " << endl;
        encryptKey();
        getch();
        system("cls");
        goto menu;
    }
    case 2:
    {
        cout << "  ************************  " << endl;
        cout << "       ENKRIPSI PESAN       " << endl;
        cout << "  ************************  " << endl;
        encryptMessage();
        getch();
        system("cls");
        goto menu;
    }
    case 3:
    {
        cout << "  ************************  " << endl;
        cout << "       DEKRIPSI PESAN       " << endl;
        cout << "  ************************  " << endl;
        decryptMessage();
        getch();
        system("cls");
        goto menu;
    }
    case 4:
    {
        cout << "  ************************  " << endl;
        cout << "       DEKRIPSI KUNCI       " << endl;
        cout << "  ************************  " << endl;
        decryptKey();
        getch();
        system("cls");
        goto menu;
    }
    case 5:
    {
        getch();
        system("cls");
        goto menu;
    }
    default:
        cout << "\tPilihan Anda salah, silahkan coba kembali";
        system("cls");
        goto menu;
    }
}
