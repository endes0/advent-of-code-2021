#include <iostream>
#include <string>
#include <vector>

unsigned long decode_binary(std::string binary) {
  unsigned long result = 0;
  for (auto c : binary) {
    result = result << 1;
    if (c == '1') {
      result++;
    }
  }

  return result;
}

std::vector<unsigned long> parse_stream_packets(std::string stream, bool first,
                                               int until, size_t &last_pos) {
  std::vector<unsigned long> results;

  size_t pos = (until == -1) ? 0 : last_pos;
  size_t parsed = 0;
  while (pos < stream.size() && (until == -1 || parsed < until)) {
    if (first && stream.size() - 1 - pos < 11) {
      break;
    }

    unsigned long version = decode_binary(stream.substr(pos, 3));
    unsigned long type = decode_binary(stream.substr(pos + 3, 3));
    pos += 6;

    std::vector<unsigned long> internal_results;
    switch (type) {
      case 4: {
        size_t internal_pos = pos;
        std::string num;
        do {
          num += stream.substr(internal_pos + 1, 4);

          if (stream[internal_pos] == '0') {
            break;
          }
          internal_pos += 5;
        } while (true);

        pos = internal_pos + 5;
        results.push_back(decode_binary(num));
      } break;
      default: {
        internal_results.clear();
        if (stream[pos] == '1') {
          unsigned long until = decode_binary(stream.substr(pos + 1, 11));
          pos += 12;
          for (auto result : parse_stream_packets(stream, false, until, pos)) {
            internal_results.push_back(result);
          }

        } else {
          size_t useless_pos = pos;
          unsigned long packet_len = decode_binary(stream.substr(pos + 1, 15));
          pos += 16;
          for (auto result : parse_stream_packets(
                   stream.substr(pos, packet_len), false, -1, useless_pos)) {
            internal_results.push_back(result);
          }
          pos += packet_len;
        }

        switch (type) {
          case 0: {  // Sum
            unsigned long result = 0;
            for (auto val : internal_results) {
              result += val;
            }
            results.push_back(result);
            break;
          }
          case 1: {  // product
            unsigned long result = 1;
            for (auto val : internal_results) {
              result *= val;
            }
            results.push_back(result);
            break;
          }
          case 2: {  // minimun
            unsigned long result = 0;
            bool first = true;
            for (auto val : internal_results) {
              if (first || val < result) {
                result = val;
                first = false;
              }
            }
            results.push_back(result);
            break;
          }
          case 3: {  // maximum
            unsigned long result = 0;
            bool first = true;
            for (auto val : internal_results) {
              if (first || val > result) {
                result = val;
                first = false;
              }
            }
            results.push_back(result);
            break;
          }
          case 5: {  // greather than
            results.push_back(internal_results[0] > internal_results[1]);
            break;
          }
          case 6: {  // less than
            results.push_back(internal_results[0] < internal_results[1]);
            break;
          }
          case 7: {  // equal to
            results.push_back(internal_results[0] == internal_results[1]);
            break;
          }

          default:
            break;
        }
        break;
      }
    }

    parsed++;
  }

  last_pos = pos;
  return results;
}

int main(int argc, char const *argv[]) {
  std::string stream;

  std::string line;
  std::getline(std::cin, line);

  for (auto c : line) {
    switch (c) {
      case '0':
        stream += "0000";
        break;
      case '1':
        stream += "0001";
        break;
      case '2':
        stream += "0010";
        break;
      case '3':
        stream += "0011";
        break;
      case '4':
        stream += "0100";
        break;
      case '5':
        stream += "0101";
        break;
      case '6':
        stream += "0110";
        break;
      case '7':
        stream += "0111";
        break;
      case '8':
        stream += "1000";
        break;
      case '9':
        stream += "1001";
        break;
      case 'A':
        stream += "1010";
        break;
      case 'B':
        stream += "1011";
        break;
      case 'C':
        stream += "1100";
        break;
      case 'D':
        stream += "1101";
        break;
      case 'E':
        stream += "1110";
        break;
      case 'F':
        stream += "1111";
        break;
      default:
        break;
    }
  }

  size_t discard;
  std::vector<unsigned long> final =
      parse_stream_packets(stream, true, -1, discard);
  std::cout << final[0] << std::endl;

  return 0;
}
