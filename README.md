# STM32 Lab 3 — Buttons and Switches

Firmware cho bài thực hành Lab 3 trên STM32F103C6. Dự án dùng kiến trúc module
để tách xử lý thời gian, nút nhấn, phần cứng hiển thị và các máy trạng thái.

## Quy ước branch

- `main`: bộ khung dùng chung, không chứa lời giải report.
- `exercise/01` đến `exercise/10`: tiến độ firmware của từng exercise.
- Report chỉ được tạo sau khi hoàn thành toàn bộ exercise và có yêu cầu riêng.

## Các module

- `software_timer`: bộ định thời phần mềm, không phụ thuộc chu kỳ ngắt cố định.
- `button`: đọc ba nút, chống dội và nhận biết nhấn giữ.
- `traffic_light`: lớp duy nhất được phép điều khiển 12 LED và bốn LED 7 đoạn.
- `fsm_manual`: chọn mode 1–4 và điều phối FSM tương ứng.
- `fsm_automatic`: vận hành đèn giao thông ở mode bình thường.
- `fsm_setting`: chỉnh thời gian đỏ, vàng và xanh ở mode 2–4.

## Phần CubeMX do người dùng cấu hình

1. Chọn STM32F103C6.
2. Cấu hình ba nút input active-low có pull-up.
3. Cấu hình GPIO output cho 12 LED giao thông và bốn LED 7 đoạn.
4. Cấu hình TIM2 phát ngắt mỗi 10 ms.
5. Generate code bằng CMake và giữ nguyên các USER CODE block trong `main.c`.

Sau khi generate, ánh xạ tên chân được bổ sung duy nhất trong
`traffic_light.c`; cấu hình ba nút được truyền cho `button_init()` trong
`main.c`. Callback TIM2 cần gọi:

```c
software_timer_tick(10U);
button_tick();
traffic_light_refresh_10ms();
```

## Build firmware

```powershell
cmake --preset Debug
cmake --build --preset Debug -j 4
```

Firmware được đặt cố định tại:

```text
build/Debug/LAB_3.hex
```
