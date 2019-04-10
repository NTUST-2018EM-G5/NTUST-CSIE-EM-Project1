# NTUST-CSIE-EM-Project1

## 測資格式
每個向量/矩陣運算功能有一個測資文字檔Vx.txt / Mx.txt
以向量為例

```
4            // 檔案中包含的向量個數
V            // 代表接下來的是向量(矩陣以M為代表)
3            // 向量維度
1 5 6        // 向量數值
V
3
2 4 10
V
3
5 4 -1
V
3
4 9 3

```

## 測試檔案
1. 在TestData資料夾中有Vector和Matrix計算測資
2. Vector包含V1-V16個運算數值，運算題目與答案請看解答.txt
3. Matrix包含M1-M12個運算數值，運算題目與答案請看解答.txt 
4. 欲確認對於大維度的測資的正確性，可使用Notepad++的文件比對工具，詳參考下列網站
http://www.moonlit.me/%E9%96%8B%E5%95%9Fnotepad%E6%96%87%E4%BB%B6%E6%AF%94%E5%B0%8D%E5%B7%A5%E5%85%B7-346.html

## 向量資料結構
```language=C++
struct Vector
{
    std::string Name;
    std::vector<double> Data;
}

int main()
{
    Vector v;
    v.Data[0] = 1;
}
```

## 矩陣資料結構
```language=C++
struct Matrix
{
    //變數名稱：輸入指令時使用
    std::string Name;
    
    //儲存向量資料
    std::vector<std::vector<double>> Data;  
}

int main()
{
    Matrix m;
    m.Data[0][0] = 1;  //[Row][Column]
}

```
## 運算元
```language=C++
struct Vector
{
    std::string Name;
    std::vector<double> Data;
    
    Vector& operator+(const Vector& v)
    {
        //Do something here
        return *this;
    }
}
```

## Distribution

### Vector Operation
- [x] Dot of Vector (1%)
- [x] Vector addition (1%)
- [x] Scalar Multiplication with vector (1%) (若vector只有一個元素時，就是Scalar)
- [x] Norm of Vector (2%)
- [x] Vector normalization (2%)
- [x] Cross product (2%)
- [x] Component of a on b (2%)
- [x] Projection of a on b (2%)
- [x] Triangle area (2%)
- [x] Parallel judgement (2%)
- [x] Orthogonal judgement (3%)
- [x] The angle between two vectors(degree) (5%)
- [x] The plane normal that is produced by two vectors (5%)
- [x] Linear independent judgement (10%)
- [x] Use Gram-schmidt to find orthonormal basis (5%)

### Matrix Operation
- [x] Matrix addition & subtraction (2%)
- [x] Matrix Multiplication (2%)
- [x] Rank of Matrix (5%)
- [x] Matrix Transpose (2%)
- [x] Solve Linear System (10%)
- [x] Determinants of Matrix (3%)
- [x] Inverse Matrix (6%)
- [x] Adjoint of Matrix (4%)
- [ ] Eigen Vector and Eigen Value (10%) (all eigen vector and eigen value)
- [ ] Power Method of Eigen value (10%)
- [x] Method of Least Square (6%)

