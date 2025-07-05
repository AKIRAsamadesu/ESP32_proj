#include "bsp.h"

esp_err_t file_system_init() {
    esp_vfs_spiffs_conf_t spiffs_conf;
    memset(&spiffs_conf, 0, sizeof(spiffs_conf));
    spiffs_conf.base_path="/img";
    spiffs_conf.partition_label="storage";
    spiffs_conf.max_files=1;
    spiffs_conf.format_if_mount_failed=true;

    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&spiffs_conf));

    size_t total=0, used=0;
    ESP_ERROR_CHECK(esp_spiffs_info(spiffs_conf.partition_label, &total, &used));

    return ESP_OK;
}

void listSPIFFS(char * path) {
	DIR* dir = opendir(path);
	assert(dir != NULL);
	while (true) {
		struct dirent*pe = readdir(dir);
		if (!pe) break;
		ESP_LOGI(__FUNCTION__,"d_name=%s d_ino=%d d_type=%x", pe->d_name,pe->d_ino, pe->d_type);
	}
	closedir(dir);
}

void showPNG(TFT_t * dev, char * file, int width, int height) {
    lcdSetFontDirection(dev, 0);
    lcdFillScreen(dev, RED);

    FILE* fp = fopen(file, "rb");
    if (fp == NULL) {
		ESP_LOGW(__FUNCTION__, "File not found [%s]", file);
		return ;
	}

    pngle_t *pngle = pngle_new(width, height);
	if (pngle == NULL) {
		ESP_LOGE(__FUNCTION__, "pngle_new fail");
		fclose(fp);
		return ;
	}

    pngle_set_init_callback(pngle, png_init);
	pngle_set_draw_callback(pngle, png_draw);
	pngle_set_done_callback(pngle, png_finish);

    double display_gamma = 2.2;
	pngle_set_display_gamma(pngle, display_gamma);

    char buf[1024];
	size_t remain = 0;
	while (!feof(fp)) {
		if (remain >= sizeof(buf)) {
			ESP_LOGE(__FUNCTION__, "Buffer exceeded");
			while(1) vTaskDelay(1);
		}

		int len = fread(buf + remain, 1, sizeof(buf) - remain, fp);
		if (len <= 0) {
			//printf("EOF\n");
			break;
		}

		int fed = pngle_feed(pngle, buf, remain + len);
		if (fed < 0) {
			ESP_LOGE(__FUNCTION__, "ERROR; %s", pngle_error(pngle));
			while(1) vTaskDelay(1);
		}

		remain = remain + len - fed;
		if (remain > 0) memmove(buf, buf + fed, remain);
	}

	fclose(fp);

	uint16_t _width = width;
	uint16_t _cols = 0;
	if (width > pngle->imageWidth) {
		_width = pngle->imageWidth;
		_cols = (width - pngle->imageWidth) / 2;
	}
	ESP_LOGD(__FUNCTION__, "_width=%d _cols=%d", _width, _cols);

	uint16_t _height = height;
	uint16_t _rows = 0;
	if (height > pngle->imageHeight) {
			_height = pngle->imageHeight;
			_rows = (height - pngle->imageHeight) / 2;
	}
	ESP_LOGD(__FUNCTION__, "_height=%d _rows=%d", _height, _rows);

	// allocate memory
	uint16_t *colors = (uint16_t*)malloc(sizeof(uint16_t) * _width);
	if (colors == NULL) {
		ESP_LOGE(__FUNCTION__, "Error allocating memory for colors");
		return ;
	}
    
    // for(int y = 0; y < _height; y++){
	// 	for(int x = 0;x < _width; x++){ 
	// 		//pixel_png pixel = pngle->pixels[y][x];
	// 		//colors[x] = rgb565(pixel.red, pixel.green, pixel.blue);
	// 		colors[x] = pngle->pixels[y][x];
	// 	}
	// 	lcdDrawMultiPixels(dev, _cols, y+_rows, _width, colors);
	// 	// vTaskDelay(1);
	// }
	lcdDrawFinish(dev);
	free(colors);
	pngle_destroy(pngle, width, height);

}