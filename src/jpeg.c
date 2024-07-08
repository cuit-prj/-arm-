#include <stdio.h>
#include "jpeglib.h"
#include "jconfig.h"
#include <stdlib.h>

int Showjpeg (char * jpegdata,int size,unsigned int *fb_mem)
{

	//һ��ΪJPEG�������ռ䲢��ʼ��
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);


	//����ָ������Դ

	jpeg_mem_src(&cinfo, jpegdata,size);


	//������ȡ�ļ���Ϣ
	(void) jpeg_read_header(&cinfo, TRUE);

	//�ġ���ѹ
	(void) jpeg_start_decompress(&cinfo);

	/* JSAMPLEs per row in output buffer */
	
	// printf("\routput_width  (%d) output_components (%d)\n", cinfo.output_width , cinfo.output_components);
	fprintf(stderr , "\r output_width  (%d) output_components (%d)", cinfo.output_width , cinfo.output_components);

	//�塢ȡ������
	int x,i;
	char *buffer;
	int row_stride = cinfo.output_width * cinfo.output_components;
	//����һ�����ݿռ�
	buffer = malloc(row_stride);

	/* Step 6: while (scan lines remain to be read) */
	/*           jpeg_read_scanlines(...); */

 
	while (cinfo.output_scanline < cinfo.output_height) 
	{
		(void) jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&buffer, 1);
		// ��24bit RGB ˢ�µ�LCD
		//��bmp_buf 24bit��ͼ������д��32bit��fb_mem

		i=0;
		for(x=0;x<cinfo.output_width;x++)
		{
			*(fb_mem+80+(cinfo.output_scanline-1)*800+x) =  buffer[i]<<16|buffer[i+1]<<8|buffer[i+2];
				i+=3;
		}
	}

	 //������ѹ���
	(void) jpeg_finish_decompress(&cinfo);
	//�ߡ��ͷ���Դ
	 jpeg_destroy_decompress(&cinfo);
  
  return 0;
}



