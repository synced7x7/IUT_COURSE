CONNECT tasnifemran/CARNIVAL864703;
SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE odd_even_counter (start_val in Number, end_val in Number)
IS 
  odd_count Number := 0;
  even_count Number := 0;

begin
  for i in start_val..end_val loop
    if MOD(i,2) = 0 then
      even_count := even_count + 1;
    else
      odd_count := odd_count + 1;
    end if;
  end loop;

    DBMS_OUTPUT.PUT_LINE('Count of odd numbers: ' || odd_count);
    DBMS_OUTPUT.PUT_LINE('Count of even numbers: ' || even_count);

end;
/

begin
  odd_even_counter(23, 1000);
end;
/