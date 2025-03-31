#include "parser.h"
#include "image_wrapper.h"
#include "errors.h"
#include "filters/modifier.h"

int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            throw std::invalid_argument(info::TEXT);
        }
        ParseResults pars = Parse(argc, argv);
        ImageWrapper iw = ImageWrapper::ReadBmp(pars.input_file);
        Modifier m = Modifier(pars.commands);
        iw.SelfApply(m);
        iw.SelfWrite(pars.output_file);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error?";
    }
}