class Bitset {
private:
    static constexpr int N = 1e5 + 100;
    bitset<N> bits;
    int sz;
public:
    explicit Bitset(int size) : sz(size) {
        bits.reset();
    }

    void fix(int idx) {
        bits.set(idx);
    }

    void unfix(int idx) {
        bits.reset(idx);
    }

    void flip() {
        for (int i = 0; i < sz; ++i) {
            bits.flip(i);
        }
    }

    bool all() {
        return bits.count() == sz;
    }

    bool one() {
        return bits.count() > 0;
    }

    int count() {
        return static_cast<int> (bits.count());
    }

    string toString() {
        string tmp;
        for(int i = 0; i < sz; ++i){
            if (bits[i])tmp.push_back('1');
            else tmp.push_back('0');
        }
        return tmp;
    }
};