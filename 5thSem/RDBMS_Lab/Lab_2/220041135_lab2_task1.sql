CONNECT tasnifemran/CARNIVAL864703;
SET SERVEROUTPUT ON;

DECLARE 
    n Number:= 128;
    total_sum Number:= 1;
begin
  for i in 2 .. n-1 loop
    if MOD(n,i) = 0 then
      total_sum := total_sum+i;
    end if;
  end loop;

    if total_sum = n then
      DBMS_OUTPUT.PUT_LINE('PERFECT');
    else
      DBMS_OUTPUT.PUT_LINE('NOT PERFECT');
    end if;
 
end;
/