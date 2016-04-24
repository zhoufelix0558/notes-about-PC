#网页下载pdf所谓时候直接保存排版会错位，但是用系统打印机就不会出现问题
--------
问题：文档中只有英文的排版才出现错位的问题

`错乱.pdf`:
    size:186KB
    PDF Version:PDF-1.4
    Page Size:[8.26*11.69 inch]
    Producer:iText 1.4.5(by lowagie.com)
    Security Method:Password Protection
    字体：
	STSong-Light
	    Type:Type1(CID)
	    Encoding:UniGB-UCS2_H
	    Actual Font:SimSun
	    Actual Font Type:True Type
	Times-Bold
	    Type:Type1
	    Encoding:Ansi
	    Actual Font:Times New Roman
	    Actual Font Type:True Type
	Times-Roman
	    Type:Type1
	    Encoding:Ansi
	    Actual Font:Times New Roman
	    Actual Font Type:True Type

`正常.pdf`:
    size:557KB
    PDF Version:PDF-1.7
    Page Size:[8.26*11.69 inch]
    Producer:Microsoft:Print To PDF
    Security Method:No Encryption
    字体：
	CIDFont+F1(Embedded Subset)
	    Type:True Type(CID)
	    Encoding:Identity-H
	CIDFont+F2(Embedded Subset)
	    Type:True Type(CID)
	    Encoding:Identity-H
	CIDFont+F3(Embedded Subset)
	    Type:True Type(CID)
	    Encoding:Identity-H

`说明`：PDF为了识别所有的字符，给每一个文字都赋予一个唯一的编码，叫CID。
PDF文件定义了许多常用内定的`Encoding CMap`，其目的当然便是要减少PDF文件的大小。至于有那些内定的Encoding CMap，可以直接到Acrobat Reader程序目录里找CMap目录，里面便有一堆（且随着版本更新而增加）。

`原因`：STSong-Light是ISO系统的字体，windows上面安装不了，pdf在iso平台上面显示正常，英语字体中很多单词是无缝连接的，由于windows系统中没有这种字体，所以出现错位。









