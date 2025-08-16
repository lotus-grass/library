{*************************************************************************}
{*                                                                       *}
{*                   VI Olimpiada Informatyczna                          *}
{*                                                                       *}
{*   Rozwi•zanie zadania: TR‡JKOLOROWE DRZEWA BINARNE                    *}
{*   Plik:                TRO.PAS                                        *}
{*   Autor:               Marcin Mucha                                   *}
{*************************************************************************}


(* Algorytm iteracyjny z wàasnym stosem.                                 *)

type
   p_stack_node = ^t_stack_node;
   t_stack_node = record
      min_z, min_nz, max_z, max_nz : word;
      prev : p_stack_node;
   end;

const
   file_in_name = 'tro.in';
   file_out_name = 'tro.out';
   N_MAX = 50000;

var
   file_in, file_out : text;
   stack : p_stack_node;
   data : array[1..N_MAX] of char;
   n : word;

procedure read_data;
begin
   n := 0;
   repeat
      inc( n);
      read( file_in, data[n])
   until seekeof( file_in);
end;

function word_min( a, b : word) : word;
begin
   if a < b then word_min := a else word_min := b
end;

function word_max( a, b : word) : word;
begin
   if a > b then word_max := a else word_max := b
end;

procedure stack_push( var s : p_stack_node; p : p_stack_node);
begin
   p^.prev := s;
   s := p
end;

function stack_pop( var s : p_stack_node) : p_stack_node;
begin
   stack_pop := s;
   s := s^.prev
end;

procedure gen_ziel( var s : p_stack_node);
var
   i : word;
   p, q, r : p_stack_node;
begin
   for i := n downto 1 do
      begin
         new( p);
         case data[i] of
            '0' : begin
                     p^.min_nz := 0; p^.min_z := 1;
                     p^.max_nz := 0; p^.max_z := 1;
                  end;
            '1' : begin
                     q := stack_pop( s);
                     p^.min_nz := word_min( q^.min_nz, q^.min_z);
                     p^.min_z := q^.min_nz + 1;
                     p^.max_nz := word_max( q^.max_nz, q^.max_z);
                     p^.max_z := q^.max_nz + 1;
                     dispose( q);
                  end;
            '2' : begin
                     q := stack_pop( s);
                     r := stack_pop( s);
                     p^.min_nz := word_min( q^.min_nz + r^.min_z,
                                            q^.min_z + r^.min_nz);
                     p^.min_z := q^.min_nz + r^.min_nz + 1;
                     p^.max_nz := word_max( q^.max_nz + r^.max_z,
                                            q^.max_z + r^.max_nz);
                     p^.max_z := q^.max_nz + r^.max_nz + 1;
                     dispose( q); dispose( r)
                  end;
         end;
         stack_push( s, p)
      end
end;

begin
   assign( file_in, file_in_name);
   reset( file_in);
   read_data;
   close( file_in);

   stack := nil;
   gen_ziel( stack);

   assign( file_out, file_out_name);
   rewrite( file_out);
   write( file_out, word_max( stack^.max_nz, stack^.max_z), ' ');
   write( file_out, word_min( stack^.min_nz, stack^.min_z));
   dispose( stack);
   close( file_out)
end.
