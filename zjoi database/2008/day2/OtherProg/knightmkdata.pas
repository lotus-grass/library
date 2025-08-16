program knightmk;

type
        integer = longint;

procedure make(nCase, N: integer);
var
        i, j    : integer;
        filename,
        st      : string;
begin
        str(nCase, st);
        filename := 'knight' + st + '.in';

        assign(output, filename); rewrite(output);
        writeln(N);
        for i := 1 to N do begin
                repeat
                        j := random(N) + 1;
                until j <> i;
                writeln(random(1000000) + 1, ' ', j);
        end;
        close(output);
end;

begin
        randseed := 20080312;
        make(0, 5);
        make(1, 10);
        make(2, 10);
        make(3, 50);
        make(4, 60);
        make(5, 100);
        make(6, 3000);
        make(7, 10000);
        make(8, 300000);
        make(9, 1000000);
end.