Bảng History và history type mọi người tự chạy thử trên ctrinh của mọi người rồi lưu vào db nhé, cái đó t không tạo data nữa còn mọi người chạy file theo thứ tự t dã đề trên tên các file, bắt dầu chạy từ 1 để tránh lỗi conflict dữ liệu chỉ cần mở file bấn run file là được,chạy 1 lần là xong 
Cài thư viện mysql.connector bằng lệnh: pip install mysql-connector-python 
Thêm 1 thư viện requests để lưu file: python -m pip install requests trên window , 
sau đó chạy câu lênh : create database Project trên query của mysql trước khi chạy code thì phải chạy mysql để ý điền thông tin của mọi người vào database ở những dòng code đầu tiên, cái user thì t để mặc định là root còn của mọi người có thể là cái khác thì phải sửa lại, password nếu không đặt thì để nguyên, đặt thì điền vào biến passwd
