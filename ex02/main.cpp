#include "PmergeMe.hpp" // PmergeMe 클래스 정의를 포함합니다.
#include <iostream> // 표준 입출력 스트림(cout, cerr)을 위해 포함합니다.
#include <cstdlib>  // atoi, exit, EXIT_FAILURE 등을 위해 포함합니다.
#include <cctype>   // isdigit 함수를 위해 포함합니다.
#include <vector>   // std::vector 컨테이너를 위해 포함합니다.
#include <deque>    // std::deque 컨테이너를 위해 포함합니다.
#include <utility>  // std::pair, std::make_pair를 위해 포함합니다.

int main(int ac, char *av[]) // main 함수: 프로그램의 시작점. ac는 인자의 개수, av는 인자 문자열 배열
{
    // 명령줄 인자가 프로그램 이름(av[0])만 있는 경우 오류 처리
    if (ac < 2) {
        std::cerr << "Error: 정렬할 숫자를 입력해주세요." << std::endl; // 오류 메시지 출력
        return EXIT_FAILURE; // 실패 코드 반환
    }
    // 인자의 개수(프로그램 이름 제외 ac - 1)가 홀수인지 확인하고 처리
    if ((ac - 1) % 2 != 0)
    {
        PmergeMe::flag = true;
        // 마지막 인자(홀수 값)를 unsigned int로 변환하기 전에 유효성 검사
        for (int i = 0; av[ac - 1][i]; ++i) {
            if (!isdigit(av[ac - 1][i])) { // 숫자가 아닌 문자가 포함되어 있는지 확인
                 std::cerr << "Error: 입력에 잘못된 문자가 있습니다: " << av[ac - 1] << std::endl; // 오류 메시지 출력
                 return EXIT_FAILURE; // 실패 코드 반환
            }
        }
        int last_val = std::atoi(av[ac - 1]); // 마지막 인자를 int로 변환
        if (last_val < 0) {
            std::cerr << "Error: 잘못된 입력: 0보다 작은 숫자입니다.\n";
            return EXIT_FAILURE;
        }

        PmergeMe::tmp = static_cast<unsigned int>(last_val); // 마지막 인자를 unsigned int로 변환하여 정적 멤버 tmp에 저장
        ac -= 1; // 홀수 인자를 제외했으므로 인자 개수 1 감소 (이제 ac는 짝수 개 쌍의 수 + 1)
    }

    std::cout << "Before : "; // 정렬 전 상태 출력 메시지

    // 정렬 전 입력 인자들을 출력 (최대 5개 쌍 + 홀수 값)
    // 출력할 인자 개수 제한 설정: 프로그램 이름(av[0]) 제외하고 최대 5개 쌍의 숫자 (총 10개 숫자) + 프로그램 이름
    int print_limit = (ac > 6) ? 6 : ac; // ac가 6보다 크면 6 (av[0] + 5개 쌍), 아니면 ac (전체 쌍 + av[0])

    if (PmergeMe::flag) { // 홀수 인자가 있었던 경우
         // 출력 제한을 프로그램 이름 + 5개 쌍 + 홀수 값 (총 11개 숫자 + 프로그램 이름)으로 조정
         // ac는 이미 1 감소된 상태이므로, 원래 인자 개수는 ac + 1
         print_limit = (ac + 1 > 6) ? 6 : ac + 1; // 원래 인자 개수가 6보다 크면 6, 아니면 원래 인자 개수
    }

    for (int i = 1; i < print_limit; ++i) { // 프로그램 이름(av[0])을 제외하고 출력
        std::cout << av[i] << " ";
    }
    // 인자가 5개 쌍을 초과하거나 (홀수 값 포함 시) 6개 이상인 경우 [...] 출력
    // 원래 인자 개수가 6보다 크거나 (ac > 6) 또는 홀수 인자가 있었고 원래 인자 개수가 6보다 크면 (PmergeMe::flag && ac + 1 > 6)
    if (ac > 6 || (PmergeMe::flag && ac + 1 > 6)) {
         std::cout << "[...]";
    }
    std::cout << std::endl;
    // --- std::vector 구현 ---
    std::vector<std::pair<unsigned int, unsigned int> > vec; // unsigned int 쌍을 저장할 vector 컨테이너
    for (int i = 1; i < ac; i += 2) // 인자들을 두 개씩 묶어서 처리 (프로그램 이름 제외, ac는 홀수 값 제외 후 개수)
    {
        // 기본적인 숫자 문자 유효성 검사 (더 강력한 검사는 checkInput에 추가 가능)
        if (isdigit(*av[i]) && isdigit(*av[i+1])) // 두 인자 모두 숫자로 시작하는지 확인
        {
             int val1 = std::atoi(av[i]); // 첫 번째 숫자를 int로 변환
             int val2 = std::atoi(av[i+1]); // 두 번째 숫자를 int로 변환

             if (val1 < 0 || val2 < 0) { // 음수인지 확인
                 std::cerr << "Error: 잘못된 입력: 0보다 작은 숫자입니다.\n"; // 오류 메시지 출력
                 return EXIT_FAILURE; // 실패 코드 반환
             }

            // 쌍을 만들어 vector에 추가 (unsigned int로 변환)
            vec.push_back(std::make_pair(static_cast<unsigned int>(val1), static_cast<unsigned int>(val2)));
        } else {
             std::cerr << "Error: 입력에 잘못된 문자가 있습니다." << std::endl; // 오류 메시지 출력
             return EXIT_FAILURE; // 실패 코드 반환
        }
    }

    std::vector<unsigned int> vec_a, vec_b; // 정렬 결과를 저장할 vector들 (calc 함수에서 사용)

    // calc 함수 호출 (vector 버전) - calc는 템플릿 함수이지만 PmergeMe 객체의 멤버입니다.
    PmergeMe sorter_vec; // vector 정렬을 위한 PmergeMe 객체 생성
    // calc 함수 호출: 인자 개수, 인자 배열, 쌍 vector, 정렬 결과 vector_a, 정렬 결과 vector_b, 컨테이너 타입 ('v' for vector)
    sorter_vec.calc(ac, av, vec, vec_a, vec_b, 'v');


    // --- std::deque 구현 ---
    std::deque<std::pair<unsigned int, unsigned int> > dec; // unsigned int 쌍을 저장할 deque 컨테이너

    for (int i = 1; i < ac; i += 2) // 인자들을 두 개씩 묶어서 처리 (프로그램 이름 제외, ac는 홀수 값 제외 후 개수)
    {
        // 기본적인 숫자 문자 유효성 검사
        if (isdigit(*av[i]) && isdigit(*av[i+1])) // 두 인자 모두 숫자로 시작하는지 확인
        {
             int val1 = std::atoi(av[i]); // 첫 번째 숫자를 int로 변환
             int val2 = std::atoi(av[i+1]); // 두 번째 숫자를 int로 변환

             if (val1 < 0 || val2 < 0) { // 음수인지 확인
                 std::cerr << "Error: 잘못된 입력: 0보다 작은 숫자입니다.\n"; // 오류 메시지 출력
                 return EXIT_FAILURE; // 실패 코드 반환
             }

            // 쌍을 만들어 deque에 추가 (unsigned int로 변환)
            dec.push_back(std::make_pair(static_cast<unsigned int>(val1), static_cast<unsigned int>(val2)));
        } else {
             std::cerr << "Error: 입력에 잘못된 문자가 있습니다." << std::endl; // 오류 메시지 출력
             return EXIT_FAILURE; // 실패 코드 반환
        }
    }
    std::deque<unsigned int> dec_a, dec_b; // 정렬 결과를 저장할 deque들 (calc 함수에서 사용)
    PmergeMe sorter_deque; // deque 정렬을 위한 PmergeMe 객체 생성 (vector와 별개의 객체)
    // calc 함수 호출: 인자 개수, 인자 배열, 쌍 deque, 정렬 결과 deque_a, 정렬 결과 deque_b, 컨테이너 타입 ('d' for deque)
    sorter_deque.calc(ac, av, dec, dec_a, dec_b, 'd');
    return EXIT_SUCCESS;
}
