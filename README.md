1. Compare pub_sub vs server_client?
- Pubsub:
+ Có xu hướng dành cho các mục đích khác nhau: bạn subscribe thứ gì đó, xử lí nó và publish nó.
+ Thường ở một tỉ lệ khá cố định. Bạn có thể đăng kí nhiều thứ và xuất bản nhiều thứ. 
+ Nhiều nút khác có thể đăng kí vào cùng topic.
+ Thậm chí có thể có nhiều node publish cùng một topic.
- Ser_cli:
+ Có xu hướng phản hồi yêu cầu nhiều hơn
+ Trong server_client. một client đưa ra yêu cầu rõ ràng với một dữ liệu cụ thể

Ví du:
  Trong pubsub nếu người dùng a và b đưa ra yêu cầu và bạn xử lí chúng và xuất ra hai phản hổi, làm thế nào để
họ biết câu trả lời nào dành cho a và câu tl nào dành cho b.
  Đó là ý nghĩa của ser_cli: đưa ra yêu cầu rõ ràng, trong khi pubsub 
