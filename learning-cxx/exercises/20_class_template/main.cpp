#include "../exercise.h"
#include <numeric>
#include <cstring>
#include <vector>

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        // TODO: 填入正确的 shape 并计算 size
        std::memcpy(shape, shape_, 4 * sizeof(unsigned int));
        unsigned int size = std::accumulate(shape, shape + 4, 1, [](const auto &a, const auto &b) {return a * b;});
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为 1。
    // `others` 长度为 1 但 `this` 长度不为 1 的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3 个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法
        std::vector<size_t> strides_this = strides(std::vector<size_t>(shape, shape + 4));
        std::vector<size_t> strides_others = strides(std::vector<size_t>(others.shape, others.shape + 4));
        unsigned int count = std::accumulate(others.shape, others.shape + 4, 1, [](const auto &a, const auto &b) {return a * b;});
        const T *src_bak = nullptr;
        for(size_t i0 = 0; i0 < shape[0]; ++i0) {
            for(size_t i1 = 0; i1 < shape[1]; ++i1) {
                for(size_t i2 = 0; i2 < shape[2]; ++i2) {
                    const T *src = others.data + i0 * strides_others[0] + i1 * strides_others[1] + i2 * strides_others[2];
                    if(src - others.data >= count) src = src_bak;
                    src_bak = src;
                    for(size_t i3 = 0; i3 < shape[3]; ++i3) {
                        data[i0 * strides_this[0] + i1 * strides_this[1] + i2 * strides_this[2] + i3 * strides_this[3]] += *src;
                        if(others.shape[3] != 1) src += strides_others[3];
                    }
                }
            }
        }
        return *this;
    }

    // @brief 计算连续存储张量的步长
    // @param shape 张量的形状
    // @return 张量每维度的访问步长
    static std::vector<size_t> strides(std::vector<size_t> const &shape) {
        std::vector<size_t> strides(shape.size());
        *strides.rbegin() = 1;
        auto ia = strides.rbegin() + 1;
        auto ib = shape.rbegin();
        for(; ia != strides.rend(); ++ia, ++ib) {
            *ia = *(ia - 1) * *ib;
        }
        return strides;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (unsigned int i = 0; i < sizeof(data) / sizeof(int); i++) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (unsigned int i = 0; i < sizeof(d0) / sizeof(int); i++) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (unsigned int i = 0; i < sizeof(d0) / sizeof(*d0); i++) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
