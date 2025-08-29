#include <iostream>
#include <vector>

using namespace std;

class Complex2
{
    private:
    int m_real, m_imag;
    
    public:
    Complex2()
    {
        m_real = 0;
        m_imag = 0;
    }
    
    Complex2(int x, int y)
    {
        m_real = x;
        m_imag = y;
    }
    
    // Overloading the  != operator
    friend bool operator!=(const Complex2& a, const Complex2& b)
    {
        return (a.m_real != b.m_real) || (a.m_imag != b.m_imag);
    }
    
    // The function performs Complex number multiplication and returns a Complex2 object.
    Complex2 complex_mul(const Complex2& obj) const
    {
        return Complex2(((m_real * obj.m_real) - (m_imag * obj.m_imag)),((m_real * obj.m_imag) + (m_imag*obj.m_real)));
    }
    
    // Overloading the ostream operator to print the objects of the Complex2 object
    friend ostream& operator<<(ostream& out, const Complex2& obj) {
        out << "(" << obj.m_real << " : " << obj.m_imag << "i)";
        return out;
    }
};
