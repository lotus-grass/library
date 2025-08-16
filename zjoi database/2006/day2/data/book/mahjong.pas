program Mahjong;

const
	st	=	'00110';
	inf	=	'mahjong.in';
	ouf	=	'mahjong.out';
	maxn	=	100;

var
	f	:	array [ 0 .. maxn , 0 .. 6 , 0 .. 6 ] of boolean;
	a	:	array [ -2 .. maxn ] of longint;
	n	:	longint;

procedure openfile;
    begin
	assign ( input , inf ) ; reset ( input );
	assign ( output , ouf ) ; rewrite ( output );
    end;

procedure init;
    var
	i	:	longint;
    begin
	fillchar ( a , sizeof ( a ) , 0 );
	for i := 1 to maxn do read ( a [ i ] );
    end;

function ok ( x : longint ) : boolean;
    begin
	if ( x > 5 ) or ( x = 0 ) then ok := true else
                if x < 0 then ok := false else ok := st [ x ] = '1';
    end;

function min ( a , b : longint ) : longint;
    begin
	if a < b then min := a else min := b;
    end;

function match : boolean;
    var
	i , j , k	:	longint;
	p , l           :	longint;
    begin
	fillchar ( f , sizeof ( f ) , false );
	match := true;
	f [ 0 , 0 , 0 ] := true;
	for i := 1 to maxn do
		for j := 0 to 6 do
                        for k := 0 to j do
                                for l := 0 to 6 do
                                begin
                                        if f [ i - 1 , l , j - k ] and ok ( a [ i - 2 ] - ( l + k ) ) then
                                        begin
                                                f [ i ,  j , k ] := true ; break;
                                        end;
                                end;
        for i := 0 to 6 do
        if ok ( a [ maxn - 1 ] - i ) then
                for j := 0 to 6 do
                if ok ( a [ maxn ] - j ) then
                        if f [ maxn , i , j ] then exit;
	match := false;
    end;

function check : boolean;
    var
	i	:	longint;
    begin
	check := true;
	for i := 1 to maxn do
	if a [ i ] >= 2 then
	begin
		a [ i ] := a [ i ] - 2;
		if match then exit;
		a [ i ] := a [ i ] + 2;
	end;
	check := false;
    end;

procedure main;
    var
	i	:	longint;
    begin
	readln ( n );
	for i := 1 to n do
	begin
		init;
		if check then writeln ( 'Yes' ) else writeln ( 'No' );
	end;
    end;

procedure closefile;
    begin
	close ( input );
	close ( output );
    end;

begin
	openfile;
	main;
	closefile;
end.