#include "PmergeMe.hpp" // PmergeMe 클래스 선언이 있는 헤더 파일 포함
#include <iostream> // 표준 입출력 스트림(cerr)을 위해 포함
#include <cstdlib>  // exit, EXIT_FAILURE, atol 등을 위해 포함
#include <cctype>   // isdigit 함수를 위해 포함
#include <limits>   // std::numeric_limits를 위해 포함 (unsigned int 최대값 확인용)

bool PmergeMe::flag = false;
unsigned int PmergeMe::tmp = 0;
PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &a)
{
    (void)a;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &a)
{
    if (this != &a) 
    {
    }
    return (*this);
}

void PmergeMe::checkInput(char *av1, char *av2)
{
    for (int i = 0; av1[i]; ++i) { // 첫 번째 문자열 검사
        if (!isdigit(av1[i])) { // 숫자가 아닌 문자를 찾으면
            std::cerr << "Error: 잘못된 입력: 숫자가 아닌 문자가 포함되어 있습니다: " << av1 << std::endl; // 오류 메시지 출력
            exit(EXIT_FAILURE); // 프로그램 비정상 종료
        }
    }
     for (int i = 0; av2[i]; ++i) { // 두 번째 문자열 검사
        if (!isdigit(av2[i])) { // 숫자가 아닌 문자를 찾으면
            std::cerr << "Error: 잘못된 입력: 숫자가 아닌 문자가 포함되어 있습니다: " << av2 << std::endl; // 오류 메시지 출력
            exit(EXIT_FAILURE); // 프로그램 비정상 종료
        }
    }

    // 숫자로 변환한 후 음수인지 체크
    long val1 = std::atol(av1); // atol을 사용하여 long 타입으로 변환 (더 큰 숫자 처리 가능)
    long val2 = std::atol(av2); // atol을 사용하여 long 타입으로 변환

    if (val1 < 0 || val2 < 0) // 둘 중 하나라도 음수이면
    {
        std::cerr << "Error: 잘못된 입력: 0보다 작은 숫자입니다.\n"; // 오류 메시지 출력
        exit(EXIT_FAILURE); // 프로그램 비정상 종료
    }

    // (선택 사항) 값이 unsigned int의 최대값을 초과하는지 확인
    if (val1 > std::numeric_limits<unsigned int>::max() || val2 > std::numeric_limits<unsigned int>::max()) {
         std::cerr << "Error: 입력 숫자가 unsigned int의 최대 허용 값을 초과합니다.\n"; // 오류 메시지 출력
         exit(EXIT_FAILURE); // 프로그램 비정상 종료
    }
}