PROGRAM Part10;
VAR
   number     : INTEGER;
   a, b, c, x : INTEGER;
   y          : REAL;

PROCEDURE P1(a : REAL);
VAR
   k : INTEGER;
BEGIN {P1}
    a := 10;
    k := 1;
    number := 3;
END;  {P1}
BEGIN {Part10}
   BEGIN
      b := 10 * a + 3 * number DIV 4;
      c := a - - b
   END;
   x := 11;
   y := 10 / 4 + 3.14;
   { writeln('a = ', a); }
   { writeln('b = ', b); }
   { writeln('c = ', c); }
   { writeln('number = ', number); }
   { writeln('x = ', x); }
   { writeln('y = ', y); }
END.  {Part10}
