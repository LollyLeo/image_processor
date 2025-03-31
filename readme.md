## Supported Image Format

Input and output image files must be in [BMP format](http://en.wikipedia.org/wiki/BMP_file_format).  

The BMP format supports many variations, but this project uses **24-bit uncompressed BMP without a color table**. The `DIB header` type must be `BITMAPINFOHEADER`.  

Example files in the required format can be found:  
- In the Wikipedia article under ["Example 1"](https://en.wikipedia.org/wiki/BMP_file_format#Example_1).  
- In the [`test_script/data`](test_script/data) directory.  

**Important**: During testing, ensure your test images are saved as **24-bit BMP**.  

---

## Command-Line Argument Format

The command-line syntax is as follows:  

```bash
{program_name} {input_file_path} {output_file_path} \
[-{filter_name_1} [filter_param_1] [filter_param_2] ...] \
[-{filter_name_2} [filter_param_1] [filter_param_2] ...] ...
```

If launched without arguments, the program displays a help message.  

### Example  
```bash
./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -vshrink 300
```

**Step-by-step execution**:  
1. Loads the image from `input.bmp`.  
2. Crops it to `800x600` pixels (starting from the top-left corner).  
3. Converts it to grayscale.  
4. Applies vertical resizing to a height of `300` pixels.  
5. Saves the result to `/tmp/output.bmp`.  

**Notes**:  
- The filter list may be empty (saves the original image unchanged).  
- Filters are applied **in the order they appear** in the command. 

## Filters

| Filter       | Description                                      | Usage                     | Example               |
|--------------|--------------------------------------------------|---------------------------|-----------------------|
| **`-gs`**    | Convert image to grayscale.                      | `-gs`                     | `-gs`                 |
| **`-crop`**  | Crop the image (top-left corner).                | `-crop <width> <height>`  | `-crop 800 600`       |
| **`-sharp`** | Enhance image sharpness                          | `-sharp`                  | `-sharp`              |
| **`-edge`**  | Highlight edges with adjustable intensity.       | `-edge <threshold>`       | `-edge 0.5`           |
| **`-vshrink`** | Vertically resize (shrink/stretch height).     | `-vshrink <new_height>`   | `-vshrink 300`        |
| **`-hshrink`** | Horizontally resize (shrink/stretch width).    | `-hshrink <new_width>`    | `-hshrink 400`        |
| **`-shrink`**  | Resize to exact dimensions (may stretch).      | `-shrink <height> <width>`| `-shrink 300 400`     |