const languageButton = document.querySelector('#language');
const tutorialLink = document.querySelector('#tutorial-link');
function setLanguage(language) {
  document.documentElement.lang = language;
  document.querySelectorAll('[data-en][data-ko]').forEach(element => {
    // These strings are authored in this page; only the headings contain markup.
    element.innerHTML = element.dataset[language];
  });
  languageButton.textContent = language === 'en' ? '한국어' : 'English';
  languageButton.setAttribute('aria-label', language === 'en' ? 'Switch to Korean' : '영어로 전환');
  tutorialLink.href = language === 'en'
    ? 'lessons/en/index.html'
    : 'lessons/ko/index.html';
  document.title = language === 'en' ? 'Small C++ — Start small. Go further.' : 'Small C++ — 작게 시작해서, 더 멀리.';
  document.querySelector('#ide-screenshot').alt = language === 'en'
    ? 'Small C++ desktop IDE with a drawing program, Run and Debug controls, and diagnostics'
    : '그림 프로그램, 실행과 디버그 도구, 진단 창을 보여 주는 Small C++ IDE';
}
languageButton.addEventListener('click', () => {
  setLanguage(document.documentElement.lang === 'en' ? 'ko' : 'en');
});
document.querySelectorAll('[data-theme]').forEach(button => {
  button.addEventListener('click', () => {
    document.querySelector('#ide-screenshot').src = `assets/ide-${button.dataset.theme}.png`;
    document.querySelectorAll('[data-theme]').forEach(option => {
      option.setAttribute('aria-pressed', String(option === button));
    });
  });
});
setLanguage('en');
