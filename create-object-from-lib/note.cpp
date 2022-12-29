- C++ có nạp chồng hàm, nên tên hàm có thể giống nhau nên khi biên dịch nó sẽ phân giải 
thành các tên khác nhau, ví dụ tên hàm là getObject thì symbol sẽ là z9xgetObjecta21 
- C thì k có nạp chồng hàm, tên hàm luôn là duy nhất, vậy nên nó sẽ không phân giải,
hàm getObject thì symbol vẫn là getObject 

dùng objdump -t binary để biết symbol tương ứng

- cách này là build project như 1 lib, trả về 1 object, thì hàm resolve yêu cầu function phải
là nguyên bản thì mới resolve được -> dùng extern "C" nếu build ở cpp

- có phải khi mà app host nó load lib nó get ra object, thì lúc này thực chất là object
đang ở chung process với app host, nó hoàn toàn tương tự kiểu 1 class trong file ở trong project,
chẳng qua là viết ở 1 project khác nên kiểu cách trông nó lạ, bản chất thì chỉ có thế

=> dùng chungh hết qquickview, rootobject, context ... 