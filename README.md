# Paint - Graphic Editor

## Installation

Simply run Assg3_2ndTry.cbp to open project. If you don't have to means to open the project, use exe file to run the project executable, ie paint.exe

## Description

As you create a rectangle, it needs to be stored in a linked list that behaves like a stack. If you view the
current code, we create a rectangle and it goes away as soon as we draw a new rectangle. This should not
happen because now we will save all the rectangles in the linked list. You will then need to go through the
entire linked list and draw every rectangle. It behaves like a stack because the new rectangle will be
drawn on top of the previous rectangle. Every time you draw something, it will have a random color.

You should draw the rectangle by default, but if you press ‘P’ you start drawing a Point on mouse click. If
your press ‘L’ you will start drawing a line. At any time you press the ‘Down Arrow’ key, your drawn
object will move down in the list. Suppose you drew a red rectangle and then drew a white rectangle on
top of the red rectangle and then you press the down arrow key, the red rectangle will now be drawn on
top of the white rectangle. The process will reverse if I now press the ‘Up Arrow’ key.

With the left mouse button we finish drawing a rectangle or any other object. With the right mouse button
we should be able to undo what we have done so far, but by pressing the middle moose button we will be
able to redo what we did in the past. In case you undo a few drawings and start drawing, then you will not
be able to redo everything that was undone.

## Screenshots

<table>
  <tbody>
    <tr>
      <!-- Video 1 -->
      <td align="center">
          <img width="390" alt="FamiChat" src="/screenshots/Screenshot%20(670).png">
          <br>
      </td>
      <!-- Video 2 -->
      <td align="center">
          <img width="390" alt="FamiChat" src="/screenshots/Screenshot%20(671).png">
          <br>
      </td>
    </tr>
    <tr>
      <td align="center">
          <img width="390" alt="FamiChat" src="/screenshots/Screenshot%20(672).png">
          <br>
      </td>
      <!-- Video 1 -->
      <td align="center">
          <img width="390" alt="FamiChat" src="/screenshots/Screenshot%20(673).png">
          <br>
      </td>
     <tr>
  </tbody>
</table>
