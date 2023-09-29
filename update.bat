@echo off
setlocal

:: Đường dẫn đến thư mục bạn muốn cập nhật
set target_folder=%cd%

:: Đường dẫn của kho lưu trữ GitHub
set github_repo=https://github.com/thanhbinhs/ChessGame.git

:: Kiểm tra xem thư mục đã tồn tại chưa, nếu chưa thì tạo mới
if not exist "%target_folder%" (
    mkdir "%target_folder%"
)

:: Di chuyển đến thư mục đích
cd "%target_folder%"

:: Clone hoặc cập nhật kho lưu trữ GitHub
if exist ".git" (
    echo Updating existing repository...
    git pull
) else (
    echo Cloning repository...
    git clone "%github_repo%" .
)

:: Kết thúc script
echo Update completed.
pause
