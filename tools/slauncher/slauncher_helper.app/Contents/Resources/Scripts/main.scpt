FasdUAS 1.101.10   ��   ��    k             i         I      �� 	���� 0 getparentpath GetParentPath 	  
�� 
 o      ���� 0 thefile theFile��  ��    O    
    L    	   n        m    ��
�� 
ctnr  o    ���� 0 thefile theFile  m       �                                                                                  MACS  alis    Z  Home                       �<ؿH+    -
Finder.app                                                       ��ǟ1t        ����  	                CoreServices    �=I?      ǟ��      -   �   �  +Home:System:Library:CoreServices:Finder.app    
 F i n d e r . a p p  
  H o m e  &System/Library/CoreServices/Finder.app  / ��        l     ��������  ��  ��        i        I     �� ��
�� .GURLGURLnull��� ��� TEXT  o      ���� 0 this_url this_URL��    k     ^       l     ��  ��    0 * display dialog "handling url " & this_URL     �   T   d i s p l a y   d i a l o g   " h a n d l i n g   u r l   "   &   t h i s _ U R L      l     ��   !��     0 * try running with release mode, then debug    ! � " " T   t r y   r u n n i n g   w i t h   r e l e a s e   m o d e ,   t h e n   d e b u g   # $ # l     �� % &��   % 9 3 the installed path for the slauncher_helper.app is    & � ' ' f   t h e   i n s t a l l e d   p a t h   f o r   t h e   s l a u n c h e r _ h e l p e r . a p p   i s $  ( ) ( l     �� * +��   * 2 ,  base_dir/lib/sirikata/slauncher_helper.app    + � , , X     b a s e _ d i r / l i b / s i r i k a t a / s l a u n c h e r _ h e l p e r . a p p )  - . - l     �� / 0��   / , & but we need to run the wrapper binary    0 � 1 1 L   b u t   w e   n e e d   t o   r u n   t h e   w r a p p e r   b i n a r y .  2 3 2 l     �� 4 5��   4    basedir/bin/slauncher    5 � 6 6 .     b a s e d i r / b i n / s l a u n c h e r 3  7 8 7 l     �� 9 :��   9 7 1 so we get a base path, then construct full paths    : � ; ; b   s o   w e   g e t   a   b a s e   p a t h ,   t h e n   c o n s t r u c t   f u l l   p a t h s 8  < = < r      > ? > l     @���� @ I    �� A��
�� .earsffdralis        afdr A  f     ��  ��  ��   ? o      ���� 0 my_path   =  B C B r     D E D I    �� F���� 0 getparentpath GetParentPath F  G�� G o   	 
���� 0 my_path  ��  ��   E o      ���� 0 lib_sirikata_path   C  H I H r     J K J I    �� L���� 0 getparentpath GetParentPath L  M�� M o    ���� 0 lib_sirikata_path  ��  ��   K o      ���� 0 lib_path   I  N O N r    " P Q P I     �� R���� 0 getparentpath GetParentPath R  S�� S o    ���� 0 lib_path  ��  ��   Q o      ���� 0 	base_path   O  T U T r   # , V W V l  # * X���� X n   # * Y Z Y 1   ( *��
�� 
psxp Z l  # ( [���� [ b   # ( \ ] \ l  # & ^���� ^ c   # & _ ` _ o   # $���� 0 	base_path   ` m   $ %��
�� 
ctxt��  ��   ] m   & ' a a � b b  b i n :��  ��  ��  ��   W o      ���� 0 installed_bin_path   U  c�� c Q   - ^ d e f d k   0 ; g g  h i h l  0 0�� j k��   j B < installed version: slauncher_helper.app is in lib/sirikata/    k � l l x   i n s t a l l e d   v e r s i o n :   s l a u n c h e r _ h e l p e r . a p p   i s   i n   l i b / s i r i k a t a / i  m n m l  0 0�� o p��   o C = and the wrapper for slauncher that sets up DYLD_LIBRARY_PATH    p � q q z   a n d   t h e   w r a p p e r   f o r   s l a u n c h e r   t h a t   s e t s   u p   D Y L D _ L I B R A R Y _ P A T H n  r s r l  0 0�� t u��   t   is in bin/    u � v v    i s   i n   b i n / s  w�� w r   0 ; x y x I  0 9�� z��
�� .sysoexecTEXT���     TEXT z b   0 5 { | { b   0 3 } ~ } o   0 1���� 0 installed_bin_path   ~ m   1 2   � � �   s l a u n c h e r   - - u r i = | o   3 4���� 0 this_url this_URL��   y 1      ��
�� 
rslt��   e R      ������
�� .ascrerr ****      � ****��  ��   f Q   C ^ � � � � r   F Q � � � I  F O�� ���
�� .sysoexecTEXT���     TEXT � b   F K � � � b   F I � � � o   F G���� 0 installed_bin_path   � m   G H � � � � � $ s l a u n c h e r _ d   - - u r i = � o   I J���� 0 this_url this_URL��   � 1      ��
�� 
rslt � R      ������
�� .ascrerr ****      � ****��  ��   � I  Y ^�� ���
�� .sysodlogaskr        TEXT � m   Y Z � � � � � < C o u l d n ' t   r u n   s l a u n c h e r   b i n a r y .��  ��     ��� � l     ��������  ��  ��  ��       �� � � ���   � ������ 0 getparentpath GetParentPath
�� .GURLGURLnull��� ��� TEXT � �� ���� � ����� 0 getparentpath GetParentPath�� �� ���  �  ���� 0 thefile theFile��   � ���� 0 thefile theFile �  ��
�� 
ctnr�� � ��,EU � �� ���� � ���
�� .GURLGURLnull��� ��� TEXT�� 0 this_url this_URL��   � �������������� 0 this_url this_URL�� 0 my_path  �� 0 lib_sirikata_path  �� 0 lib_path  �� 0 	base_path  �� 0 installed_bin_path   � ������ a�� �������� � ���
�� .earsffdralis        afdr�� 0 getparentpath GetParentPath
�� 
ctxt
�� 
psxp
�� .sysoexecTEXT���     TEXT
�� 
rslt��  ��  
�� .sysodlogaskr        TEXT�� _)j  E�O*�k+ E�O*�k+ E�O*�k+ E�O��&�%�,E�O ��%�%j E�W "X  	 ��%�%j E�W X  	�j ascr  ��ޭ