# Windows Application using MFC Framework

## Objective
Build a Windows application using the MFC framework to manage a row of graphic elements. Each element in the row has a value (1 to 4) and other properties such as shape, color, and size. The application should draw all elements in the window in a row with ascending order.

## Features
- Initialize the window with 4 graphic elements, each with a value (1 to 4) and other properties.
- Draw all elements in the window in a row with ascending order.
- Allow the user to insert elements into the row:
  - Insert to the beginning: new element's value = original first element's value - 1
  - Insert to the end: new element's value = original last element's value + 1
  - Insert to the middle: new element's value = average of the neighboring element's value
- Allow the user to delete elements from the row, while all others remain the same.
- Auto-align the row with equal space between each element.

## Implementation
The implementation will require creating a window with the MFC framework and managing the graphic elements within the window. Drawing the elements in a row with ascending order can be achieved using a graphical library or MFC drawing functions. Implementing the insertion and deletion of elements will involve updating the values of the elements and adjusting their positions in the row. Auto-aligning the row can be done by calculating the space between each element based on the window size and the number of elements in the row.

## Conclusion
Building a Windows application using the MFC framework to manage a row of graphic elements can be a challenging but rewarding task. By implementing the features mentioned above, the application can provide a user-friendly interface for managing and visualizing the elements in the row.
