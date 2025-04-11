# ỨNG DỤNG QUẢN LÝ TÀI CHÍNH CÁ NHÂN - ĐỒ ÁN CUỐI KHÓA MÔN OOP

## Mục lục
1. [Giới thiệu](#giới-thiệu)
2. [Các tính năng chính](#các-tính-năng-chính)
3. [Cấu trúc dự án](#cấu-trúc-dự-án)
4. [Hướng dẫn tải và chạy ứng dụng](#hướng-dẫn-tải-và-chạy-ứng-dụng)
5. [Phân tích chi tiết các tính năng](#phân-tích-chi-tiết-các-tính-năng)
6. [Cách hoạt động của ứng dụng](#cách-hoạt-động-của-ứng-dụng)
7. [Video demo](#video-demo)
8. [Công nghệ sử dụng](#công-nghệ-sử-dụng)
9. [Tác giả](#tác-giả)

---

## Giới thiệu
Ứng dụng Quản lý Tài chính Cá nhân là một dự án được phát triển bằng ngôn ngữ lập trình C++ theo hướng đối tượng (OOP). Mục tiêu của ứng dụng là hỗ trợ người dùng quản lý tài chính cá nhân một cách hiệu quả, bao gồm các tính năng như quản lý tài khoản ngân hàng, giao dịch, khoản vay và cho vay, cũng như cung cấp các báo cáo chi tiết về tình hình tài chính.

---

## Các tính năng chính
### 1. **Quản lý tài khoản ngân hàng**
- **Thêm tài khoản ngân hàng:** Người dùng có thể thêm tài khoản ngân hàng mới với thông tin chi tiết.
- **Xóa tài khoản ngân hàng:** Xóa tài khoản không còn sử dụng.
- **Cập nhật số dư:** Cập nhật số dư tài khoản khi có giao dịch.
- **Hiển thị lịch sử giao dịch:** Xem chi tiết các giao dịch đã thực hiện trên từng tài khoản.
- **Tính toán số dư tổng hợp:** Tự động tính toán tổng số dư của tất cả tài khoản.

### 2. **Quản lý giao dịch**
- **Ghi nhận giao dịch:** Lưu trữ các giao dịch tài chính như chi tiêu, thu nhập.
- **Tra cứu giao dịch:** Tìm kiếm giao dịch theo mục đích hoặc khoảng thời gian.
- **Báo cáo chi tiêu:** Hiển thị báo cáo chi tiết về các khoản chi tiêu theo danh mục.

### 3. **Quản lý khoản vay và cho vay**
- **Thêm khoản vay/cho vay:** Ghi nhận các khoản vay hoặc cho vay mới.
- **Xóa khoản vay/cho vay:** Xóa các khoản vay hoặc cho vay không còn cần thiết.
- **Cập nhật khoản vay/cho vay:** Thay đổi thông tin khoản vay hoặc cho vay.
- **Tính toán lãi suất:** Hỗ trợ tính lãi suất đơn và lãi suất kép.
- **Nhắc nhở thanh toán:** Tự động nhắc nhở khi đến hạn thanh toán.
- **Hiển thị lịch sử thanh toán:** Xem chi tiết các khoản thanh toán đã thực hiện.

### 4. **Báo cáo tài chính**
- **Báo cáo tổng quan:** Hiển thị tình hình tài chính tổng thể.
- **Báo cáo chi tiết:** Phân tích chi tiết các khoản vay, cho vay, và giao dịch.
- **Tra cứu dữ liệu:** Lọc và tìm kiếm dữ liệu theo thời gian.

### 5. **Giao diện người dùng**
- **Giao diện dòng lệnh:** Đơn giản, dễ sử dụng.
- **Điều hướng:** Sử dụng phím mũi tên và phím Enter để điều hướng.
- **Hiệu ứng đồ họa:** Hiển thị tiêu đề, lời chào, và hiệu ứng tải.

---

## Cấu trúc dự án
Dự án được tổ chức thành các thư mục và tệp tin như sau:

### 1. **Thư mục `UI`**
- **Mô tả:** Chứa các tệp tin liên quan đến giao diện người dùng.
- **Chi tiết:**
  - `UI.h`: Lớp chính điều khiển giao diện, quản lý các màn hình và luồng hoạt động.
  - `ScreenADT.h`: Lớp trừu tượng cho các màn hình, định nghĩa các phương thức cơ bản như `display()` và `handleInput()`.
  - `MainScreen.h`: Màn hình chính, nơi người dùng chọn các tính năng như quản lý tài khoản, giao dịch, khoản vay.
  - `Login.h`: Xử lý đăng nhập, xác thực người dùng từ tệp `users.txt`.
  - `LoanScreen.h`: Màn hình quản lý khoản vay và cho vay, bao gồm các chức năng như thêm, xóa, cập nhật khoản vay.
  - `main.cpp`: Điểm bắt đầu của chương trình, khởi tạo giao diện và xử lý luồng chính.

### 2. **Thư mục `Manage`**
- **Mô tả:** Chứa các tệp tin quản lý dữ liệu và logic nghiệp vụ.
- **Chi tiết:**
  - `ManageUser.h`: Lớp quản lý người dùng, tích hợp các chức năng chính như quản lý tài khoản, giao dịch, khoản vay.
  - `TransactionManage.h`: Quản lý giao dịch, bao gồm thêm, xóa, và tra cứu giao dịch.
  - `BankManage.h`: Quản lý tài khoản ngân hàng, xử lý các thao tác liên quan đến tài khoản.
  - `LoanManager.h`: Quản lý khoản vay và cho vay, bao gồm tính toán lãi suất và nhắc nhở thanh toán.

### 3. **Thư mục `Loan`**
- **Mô tả:** Chứa các tệp tin liên quan đến khoản vay và cho vay.
- **Chi tiết:**
  - `Loan.h`: Lớp trừu tượng cho khoản vay và cho vay, định nghĩa các phương thức cơ bản như `addLoan()`, `makePayment()`.

### 4. **Thư mục `Transaction`**
- **Mô tả:** Chứa các tệp tin liên quan đến giao dịch.
- **Chi tiết:**
  - `Transaction.h`: Lớp đại diện cho một giao dịch, bao gồm thông tin như số tiền, mục đích, và ngày giao dịch.

### 5. **Thư mục `Date_Time`**
- **Mô tả:** Chứa các tệp tin xử lý ngày giờ.
- **Chi tiết:**
  - `CheckValidDate.h`: Kiểm tra tính hợp lệ của ngày tháng.
  - `DateUtils.h`: Các tiện ích xử lý ngày tháng như chuyển đổi định dạng.

### 6. **Thư mục `Bank`**
- **Mô tả:** Chứa các tệp tin liên quan đến tài khoản ngân hàng.
- **Chi tiết:**
  - `AccountBank.h`: Lớp đại diện cho một tài khoản ngân hàng, bao gồm thông tin như số tài khoản, tên ngân hàng, và số dư.

### 7. **Thư mục `InputFile`**
- **Mô tả:** Chứa các tệp dữ liệu đầu vào.
- **Chi tiết:**
  - `users.txt`: Danh sách người dùng và mật khẩu.
  - `inputUser.txt`: Dữ liệu tài khoản ngân hàng.
  - `inputLoan.txt`: Dữ liệu khoản vay và cho vay.

---

## Hướng dẫn tải và chạy ứng dụng
1. **Tải mã nguồn**
   - Clone dự án từ GitHub:
     ```bash
     git clone https://github.com/Nnguyen-dev2805/OOP_FinalProject.git
     ```
   - Hoặc tải trực tiếp tệp ZIP từ GitHub và giải nén.

2. **Cài đặt**
   - Mở dự án trong IDE hỗ trợ C++ như Visual Studio hoặc Code::Blocks.
   - Đảm bảo các tệp dữ liệu đầu vào (`users.txt`, `inputUser.txt`, `inputLoan.txt`) nằm trong thư mục `InputFile`.

3. **Chạy ứng dụng**
   - Biên dịch và chạy tệp `main.cpp`.
   - Làm theo hướng dẫn trên giao diện dòng lệnh.

---

## Phân tích chi tiết các tính năng
### 1. **Đăng nhập**
- Người dùng nhập tên đăng nhập và mật khẩu.
- Xác thực thông tin từ tệp `users.txt`.
- Hiển thị thông báo đăng nhập thành công hoặc thất bại.

### 2. **Quản lý tài khoản**
- Hiển thị danh sách tài khoản ngân hàng.
- Thêm tài khoản mới với thông tin chi tiết.
- Xóa tài khoản không còn sử dụng.
- Cập nhật số dư tài khoản khi có giao dịch.

### 3. **Quản lý giao dịch**
- Ghi nhận các giao dịch với thông tin như số tiền, mục đích, và ngày giao dịch.
- Tra cứu giao dịch theo mục đích hoặc khoảng thời gian.
- Hiển thị báo cáo chi tiết về các khoản chi tiêu.

### 4. **Quản lý khoản vay**
- Thêm khoản vay hoặc cho vay mới.
- Tính toán lãi suất dựa trên lãi suất đơn hoặc kép.
- Nhắc nhở khi đến hạn thanh toán.
- Hiển thị lịch sử thanh toán chi tiết.

---

## Cách hoạt động của ứng dụng
1. **Khởi động ứng dụng**
   - Người dùng đăng nhập bằng tên đăng nhập và mật khẩu.
   - Chuyển đến màn hình chính sau khi đăng nhập thành công.

2. **Điều hướng**
   - Sử dụng phím mũi tên để chọn các tính năng.
   - Nhấn Enter để xác nhận lựa chọn.

3. **Thao tác**
   - Thực hiện các thao tác như thêm tài khoản, ghi nhận giao dịch, hoặc quản lý khoản vay.
   - Dữ liệu được lưu trữ và cập nhật tự động.

---

## Video demo
[Link video demo](#) (https://www.youtube.com/watch?v=fLdZVGQxcpg)

---

## Công nghệ sử dụng
- Ngôn ngữ lập trình: C++
- Hướng đối tượng (OOP)
- Thư viện chuẩn C++ (STL)
- Xử lý tệp tin và ngày giờ

---

## Tác giả
- **Trương Nhất Nguyên**  
  - MSSV: 23110273  
  - GitHub: [Nnguyen-dev2805](https://github.com/Nnguyen-dev2805)

- **Nguyễn Hoàng Hà**  
  - MSSV: 23110207  
  - GitHub: [nguyenhoangha0710](https://github.com/nguyenhoangha0710)

- **Đặng Ngọc Tài**  
  - MSSV: 23110304  
  - GitHub: [taidang05](https://github.com/taidang05)

- **Nghiêm Quang Huy**  
  - MSSV: 23110222  
  - GitHub: [HuyinCP](https://github.com/HuyinCP)
- **Lê Minh Hưng**  
  - MSSV: 23162034 
  - GitHub: [leminhhung2005](https://github.com/HuyinCP)

