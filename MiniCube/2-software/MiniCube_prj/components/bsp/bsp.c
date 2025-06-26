#include "bsp.h"

static const char *TAG="bsp";

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
		ESP_LOGI(TAG,"d_name=%s d_ino=%d d_type=%x", pe->d_name,pe->d_ino, pe->d_type);
	}
	closedir(dir);
}